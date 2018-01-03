#include"services.h"
#include"io.h"
#include<algorithm>
using namespace std;

int Service::addCity(City x)
{
    IOCity.push_back(x);
    return SUCCESS;
}

vector<City>::iterator Service::findCity(string name)
{
    return find(IOCity.begin(), IOCity.end(), name);
}

int Service::editCity(string name, City info)
{
    auto it = findCity(name);
    if (it == IOCity.end())
        return NOT_FOUND;
    *it = info;
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