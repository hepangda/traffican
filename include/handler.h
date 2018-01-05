#pragma once
#include"forums.h"

class Handlers {
public:
    static int mainmenu(UIArguments args, UIInputDelegater dg);
    static int askMainmenu(UIArguments args, UIInputDelegater dg);

    static int exit(UIArguments args, UIInputDelegater dg);

    static int cityMgr(UIArguments args, UIInputDelegater dg);
    static int askCityMgr(UIArguments args, UIInputDelegater dg);
    static int cityAdd(UIArguments args, UIInputDelegater dg);
    static int cityEdit(UIArguments args, UIInputDelegater dg);
    static int cityDelete(UIArguments args, UIInputDelegater dg);
    static int cityList(UIArguments args, UIInputDelegater dg);

    static int routeMgr(UIArguments args, UIInputDelegater dg);
    static int askRouteMgr(UIArguments args, UIInputDelegater dg);
    static int routeAdd(UIArguments args, UIInputDelegater dg);
    static int routeDelete(UIArguments args, UIInputDelegater dg);
    static int routeList(UIArguments args, UIInputDelegater dg);

    static int advice(UIArguments args, UIInputDelegater dg);
    static int askAdvice(UIArguments args, UIInputDelegater dg);

    template<typename T>
    static int askL(UIArguments args, UIInputDelegater dg);

    static int askLprice(UIArguments args, UIInputDelegater dg);
    static int askLtime(UIArguments args, UIInputDelegater dg);
    static int askLtrans(UIArguments args, UIInputDelegater dg);
};

class HChoiceDelegater {
private:
    std::map<int, std::function<void()> > func;
    std::function<void()> ferr;
    bool hasFault = false;
    UINormal *prevUI;

    void defaultFault();
    void execFault();
public:
    HChoiceDelegater(UINormal *prevUI): prevUI(prevUI) {}
    void bind(int x, std::function<void()> f);
    void fault(std::function<void()> f);
    void act(UIArguments args, UIInputDelegater dg);
};