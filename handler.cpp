#include"handler.h"
#include"utils.h"
#include"services.h"
#include"algo.h"
using namespace std;
extern long cityidMaker;

void HChoiceDelegater::DEFAULT_FAULT()
{
    UIGlobal::clear([]()
    {
        std::cout << "   > 选项有误，请重新选择" << std::endl;
    });
    UIGlobal::set(prevUI);
}

void HChoiceDelegater::execFault()
{
    return (hasFault ? ferr() : DEFAULT_FAULT());
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

int HMainmenu(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskMainmenu);
    return 0;
}

int HExit(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::abort();
    return 0;
}

int HCityMgr(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskCityMgr);
    return 0;
}

int HRouteMgr(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskRouteMgr);
    return 0;
}

int HAdvice(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::set(UFAskAdvice);
    return 0;
}

int HAskMainmenu(UIArguments args, UIInputDelegater dg)
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

int HAskCityMgr(UIArguments args, UIInputDelegater dg)
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

int HAskRouteMgr(UIArguments args, UIInputDelegater dg)
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

int HAskAdvice(UIArguments args, UIInputDelegater dg)
{    
    HChoiceDelegater h(&UFAskAdvice);
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

int HCityAdd(UIArguments args, UIInputDelegater dg)
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

int HCityEdit(UIArguments args, UIInputDelegater dg)
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

int HCityDelete(UIArguments args, UIInputDelegater dg)
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

int HCityList(UIArguments args, UIInputDelegater dg)
{
    Service::loadCity(UFCityList); 
    UIGlobal::setAndClear(UFCityMgr);
    return 0;
}

int HRouteAdd(UIArguments args, UIInputDelegater dg)
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

int HRouteDelete(UIArguments args, UIInputDelegater dg)
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

int HRouteList(UIArguments args, UIInputDelegater dg)
{
    Service::loadRoute(UFRouteList); 
    UIGlobal::setAndClear(UFRouteMgr);
    return 0;
}

template<typename T>
static int TAskL(UIArguments args, UIInputDelegater dg)
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
        auto ret = dijkstra(from, to, tm);

        cout << "  # 根据您的要求，已为您选择最适合的出行方式：  " << endl << endl;

        for (int i = 0; i < ret.travel.size(); i++) {
            cout << "   > " << i + 1<< ". " << "乘坐 " << Service::typeStringFromID(ret.travel[i].type)
                 << " 由 " << Service::cityStringFromID(ret.travel[i].from) << " 前往 " 
                 << Service::cityStringFromID(ret.travel[i].to) << endl;
        }
        cout << endl << endl;

        if (ret.tp == -1)
            UIGlobal::clear(resNoway);
    } catch (...) {
        UIGlobal::clear(resNope);
    }

    UIGlobal::set(UFAdvice);
    return 0;
}

int HAskLprice(UIArguments args, UIInputDelegater dg)
{
    struct LP {
        Path operator()(long from, long to, Time tm)
        {
            return Algorithm::dijkstra<Algorithm::LessPrice>(from, to, tm);
        }
    };

    return TAskL<LP>(args, dg);
}

int HAskLtime(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::setAndClear(UFAdvice);
    return 0;
}

int HAskLtrans(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::setAndClear(UFAdvice);
    return 0;
}