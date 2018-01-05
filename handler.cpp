#include"handler.h"
#include"utils.h"
#include"services.h"
#include"algo.hpp"
using namespace std;
extern long cityidMaker;

void HChoiceDelegater::defaultFault()
{
    UIGlobal::clear([]()
    {
        std::cout << "   > 选项有误，请重新选择" << std::endl;
    });
    UIGlobal::set(prevUI);
}

void HChoiceDelegater::execFault()
{
    return (hasFault ? ferr() : defaultFault());
}

void HChoiceDelegater::bind(int x, function<void()> f)
{
    func[x] = f;
}

void HChoiceDelegater::fault(function<void()> f)
{
    ferr = f;
    hasFault = true;
}

void HChoiceDelegater::act(UIArguments args, UIInputDelegater dg)
{
    auto choice = dg.getInt(args[0]);
    if (!choice.vaild)
        execFault();

    if (func.find(choice.val) != func.end())
        func[choice.val]();
    else
        execFault();
}

int Handlers::mainmenu(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskMainmenu);
    return 0;
}

int Handlers::exit(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::abort();
    return 0;
}

int Handlers::cityMgr(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskCityMgr);
    return 0;
}

int Handlers::routeMgr(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskRouteMgr);
    return 0;
}

int Handlers::advice(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskAdvice);
    return 0;
}

int Handlers::askMainmenu(UIArguments args, UIInputDelegater dg)
{
    HChoiceDelegater h(&UFMainmenu);
    function<void()> doings[] = {
       []() { UIGlobal::setAndClear(UFCityMgr); },
       []() { UIGlobal::setAndClear(UFRouteMgr); },
       []() { UIGlobal::setAndClear(UFAdvice); },
       []() { UIGlobal::set(UFExit); }
    };

    for (int i = 0; i < 4; i++) {
        h.bind(i + 1, doings[i]);
    }
    
    h.act(args, dg);
    return 0;
}

int Handlers::askCityMgr(UIArguments args, UIInputDelegater dg)
{
    HChoiceDelegater h(&UFCityMgr);
    function<void()> doings[] = {
       []() { UIGlobal::set(UFCityList); },
       []() { UIGlobal::set(UFCityAdd); },
       []() { UIGlobal::set(UFCityEdit); },
       []() { UIGlobal::set(UFCityDelete); },
       []() { UIGlobal::setAndClear(UFMainmenu); }
    };

    for (int i = 0; i < 5; i++) {
        h.bind(i + 1, doings[i]);
    }
    
    h.act(args, dg);
    return 0;
}

int Handlers::askRouteMgr(UIArguments args, UIInputDelegater dg)
{    
    HChoiceDelegater h(&UFRouteMgr);
    function<void()> doings[] = {
       []() { UIGlobal::set(UFRouteList); },
       []() { UIGlobal::set(UFRouteAdd); },
       []() { UIGlobal::set(UFRouteDelete); },
       []() { UIGlobal::setAndClear(UFMainmenu); }
    };

    for (int i = 0; i < 4; i++) {
        h.bind(i + 1, doings[i]);
    }
    
    h.act(args, dg);
    return 0;
}

int Handlers::askAdvice(UIArguments args, UIInputDelegater dg)
{    
    HChoiceDelegater h(&UFAdvice);
    function<void()> doings[] = {
       []() { UIGlobal::set(UFAskLtime); },
       []() { UIGlobal::set(UFAskLprice); },
       []() { UIGlobal::set(UFAskLtrans); },
       []() { UIGlobal::setAndClear(UFMainmenu); }
    };

    for (int i = 0; i < 4; i++) {
        h.bind(i + 1, doings[i]);
    }
    
    h.act(args, dg);
    return 0;
}

int Handlers::cityAdd(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resOK = []()
    {
        std::cout << "   > 添加成功，请确认" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 该城市已存在，添加失败" << std::endl;
    };

    City info = { dg.getString(args[0]).val, dg.getString(args[1]).val, cityidMaker++ };
    UIGlobal::setAndClear(UFCityMgr, (Service::addCity(info) == Service::SUCCESS) ? resOK : resNope);
    return 0;
}

int Handlers::cityEdit(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resOK = []()
    {
        std::cout << "   > 城市介绍已更新" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 该城市不存在，编辑失败" << std::endl;
    };

    City info = { dg.getString(args[0]).val, dg.getString(args[1]).val, 0 };
    UIGlobal::setAndClear(UFCityMgr, (Service::editCity(info) == Service::SUCCESS) ? resOK : resNope);

    return 0;
}

int Handlers::cityDelete(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resOK = []()
    {
        std::cout << "   > 已删除该城市" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 要删除的城市不存在" << std::endl;
    };

    UIGlobal::setAndClear(UFCityMgr, 
        (Service::deleteCity(dg.getString(args[0]).val) == Service::SUCCESS) ? resOK : resNope);
    return 0;
}

int Handlers::cityList(UIArguments args, UIInputDelegater dg)
{
    Service::loadCity(UFCityList); 
    UIGlobal::setAndClear(UFCityMgr);
    return 0;
}

int Handlers::routeAdd(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resOK = []()
    {
        std::cout << "   > 创建线路成功！" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 创建失败！输入的数据不合法" << std::endl;
    };

    try {
        RouteRequest req = {
            dg.getString(args[0]).val, dg.getString(args[1]).val, dg.getString(args[2]).val, 
            dg.getString(args[3]).val, dg.getString(args[4]).val, dg.getInt(args[5]).val, 
        };

        UIGlobal::setAndClear(UFRouteMgr, 
            (Service::addRoute(req) == Service::SUCCESS) ? resOK : resNope);
    } catch (...) {
        UIGlobal::setAndClear(UFRouteMgr, resNope);
    }
    return 0;
}

int Handlers::routeDelete(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resOK = []()
    {
        std::cout << "   > 已删除该路线" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 要删除的路线不存在" << std::endl;
    };

    int res;
    try {
        UIGlobal::setAndClear(UFRouteMgr, 
            (Service::deleteRoute(dg.getInt(args[0]).val) == Service::SUCCESS) ? resOK : resNope);
    } catch (...) {
        UIGlobal::setAndClear(UFRouteMgr, resNope);
    }
    return 0;
}

int Handlers::routeList(UIArguments args, UIInputDelegater dg)
{
    Service::loadRoute(UFRouteList); 
    UIGlobal::setAndClear(UFRouteMgr);
    return 0;
}

template<typename T>
int Handlers::askL(UIArguments args, UIInputDelegater dg)
{
    static function<void()> resNoway = []()
    {
        std::cout << "   > 两城市之间无法到达！" << std::endl;
    };

    static function<void()> resNope = []()
    {
        std::cout << "   > 输入的数据格式有误！" << std::endl;
    };

    try {
        UIGlobal::clear();
        long from = Service::cityIDFromString(dg.getString(args[0]).val),
             to = Service::cityIDFromString(dg.getString(args[1]).val),
             tm = Service::timeFromString(dg.getString(args[2]).val);

        T dijkstra;
        auto ret = Algorithm::dijkstra<T>(from, to, tm);

        cout << "  # 根据您的要求，已为您选择最适合的出行方式：  " << endl << endl;
        long costs = 0;
        for (int i = 0; i < ret.travel.size(); i++) {
            costs += ret.travel[i].price;
            cout << "   > " << i + 1<< ". 于 " << Service::timeFromTimet(ret.travel[i].starts)
                 << " 乘坐 " << Service::typeStringFromID(ret.travel[i].type)
                 << " 由 " << Service::cityStringFromID(ret.travel[i].from) << " 前往 " 
                 << Service::cityStringFromID(ret.travel[i].to)
                 << ",并于 " << Service::timeFromTimet(ret.travel[i].ends) << " 到达." << endl;
        }
        cout << endl;
        cout << "  @ 本次旅行, 共耗时 " << Service::timeFromTimet(timeMinus(ret.travel.back().ends, tm))
             << " , 耗费 " << costs << " 元, 中转 " << ret.travel.size() - 1 << " 站." << endl << endl;

        if (ret.tp == -1)
            UIGlobal::clear(resNoway);
    } catch (...) {
        UIGlobal::clear(resNope);
    }

    UIGlobal::set(UFAdvice);
    return 0;
}

int Handlers::askLprice(UIArguments args, UIInputDelegater dg)
{
    return askL<Algorithm::LessPrice>(args, dg);
}

int Handlers::askLtime(UIArguments args, UIInputDelegater dg)
{
    return askL<Algorithm::LessTime>(args, dg);
}

int Handlers::askLtrans(UIArguments args, UIInputDelegater dg)
{
    return askL<Algorithm::LessTrans>(args, dg);
}