#include"services.h"
#include"io.h"
#include<algorithm>
#include<map>
using namespace std;
long idMaker = 0;

int Service::addCity(City x)
{
    if (findCity(x.name) != IOCity.end())
        return EXISTED;
    IOCity.push_back(x);
    return SUCCESS;
}

vector<City>::iterator Service::findCity(string name)
{
    return find(IOCity.begin(), IOCity.end(), name);
}

int Service::editCity(City info)
{
    auto it = findCity(info.name);
    if (it == IOCity.end())
        return NOT_FOUND;
    it->intro = info.intro;
    return SUCCESS;
}

int Service::deleteCity(string name)
{
    auto it = findCity(name);
    if (it == IOCity.end())
        return NOT_FOUND;
    IOCity.erase(it);
    return SUCCESS;
}

int Service::loadCity(UIForm &form)
{
    vector<int> widths = { 20, 40 };
    vector<string> titles = { "城市", "城市介绍" };
    vector<vector<string> > lists;
    lists.resize(IOCity.size());
    for (int i = 0; i < IOCity.size(); i++) {
        lists[i].push_back(IOCity[i].name);
        lists[i].push_back(IOCity[i].intro);
    }
    form.put(widths, titles, lists);

    return SUCCESS;
}

long Service::cityIDFromString(string name)
{
    auto it = findCity(name);
    if (it == IOCity.end())
        throw 1;
    return it->id;
}

string Service::cityStringFromID(long id)
{
    auto it = find(IOCity.begin(), IOCity.end(), id);
    if (it == IOCity.end())
        throw 1;
    return it->name;
}

int Service::typeIDFromString(string name)
{
    static map<string, int> convert = { {"火车", 0}, {"飞机", 1}, {"高铁", 2} };
    return convert[name];
}

string Service::typeStringFromID(int id)
{
    static map<int, string> convert = { {0, "火车"}, {1, "飞机"}, {2, "高铁"} };
    return convert[id];
}

Time Service::timeFromString(std::string ts)
{
    int h, m, s;
    sscanf(ts.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 10000 + m * 100 + s;
}

std::string Service::timeFromTimet(Time tm)
{
    int h = tm / 10000,
        m = (tm / 100) % 100,
        s = tm % 100;
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);
}

int Service::addRoute(RouteRequest x)
{  
    try {
        Route r = { cityIDFromString(x.from), cityIDFromString(x.to), x.price, typeIDFromString(x.type),
                    timeFromString(x.starts), timeFromString(x.ends), idMaker++ };
        IORoute.push_back(r);
        return SUCCESS;
    } catch (...) {
        return ERROR_MSG;
    }
}

vector<Route>::iterator Service::findRoute(long id)
{
    return find(IORoute.begin(), IORoute.end(), id);
}

int Service::deleteRoute(long id)
{
    auto it = findRoute(id);
    if (it == IORoute.end())
        return NOT_FOUND;
    IORoute.erase(it);
    return SUCCESS;
}

int Service::loadRoute(UIForm &form)
{
    vector<int> widths = { 8, 15, 15, 8, 16, 16, 8 };
    vector<string> titles = { "ID", "起点", "终点", "方式", "开始时间", "结束时间", "价格" };
    vector<vector<string> > lists;

    lists.resize(IORoute.size());
    for (int i = 0; i < IORoute.size(); i++) {
        lists[i].push_back(to_string(IORoute[i].id));
        lists[i].push_back(cityStringFromID(IORoute[i].from));
        lists[i].push_back(cityStringFromID(IORoute[i].to));
        lists[i].push_back(typeStringFromID(IORoute[i].type));
        lists[i].push_back(timeFromTimet(IORoute[i].starts));
        lists[i].push_back(timeFromTimet(IORoute[i].ends));
        lists[i].push_back(to_string(IORoute[i].price));
    }
    form.put(widths, titles, lists);

    return SUCCESS;
}