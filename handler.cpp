#include"handler.h"
using namespace std;

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
       []() { cout << "List City" << endl; },
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
       []() { cout << "List Route" << endl; },
       []() { cout << "Add Route" << endl; },
       []() { cout << "Edit Route" << endl; },
       []() { cout << "Delete Route" << endl; },
       []() { UIGlobal::setAndClear(UFMainmenu); }
    };

    for (int i = 0; i < 5; i++) {
        h.bind(i + 1, doings[i]);
    }
    
    h.act(args, dg);
    return 0;
}

int HAskAdvice(UIArguments args, UIInputDelegater dg)
{    
    HChoiceDelegater h(&UFAskAdvice);
    function<void()> doings[] = {
       []() { cout << "Fewest Time" << endl; },
       []() { cout << "Lowest Cost" << endl; },
       []() { cout << "Fewest Path" << endl; },
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
    UIGlobal::setAndClear(UFCityMgr, []()
    {
        std::cout << "   > 添加成功，请确认" << std::endl;
    });
    return 0;
}

int HCityEdit(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::setAndClear(UFCityMgr, []()
    {
        std::cout << "   > 编辑成功？失败？" << std::endl;
    });
    return 0;
}

int HCityDelete(UIArguments args, UIInputDelegater dg)
{
    UIGlobal::setAndClear(UFCityMgr, []()
    {
        std::cout << "   > 删除成功？失败？" << std::endl;
    });
    return 0;
}

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }

// int H(UIArguments args, UIInputDelegater dg)
// {
//     return 0;
// }
