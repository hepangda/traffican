#pragma once
#include"forums.h"

int HMainmenu(UIArguments args, UIInputDelegater dg);
int HAskMainmenu(UIArguments args, UIInputDelegater dg);

int HExit(UIArguments args, UIInputDelegater dg);

int HCityMgr(UIArguments args, UIInputDelegater dg);
int HAskCityMgr(UIArguments args, UIInputDelegater dg);
int HCityAdd(UIArguments args, UIInputDelegater dg);
int HCityEdit(UIArguments args, UIInputDelegater dg);
int HCityDelete(UIArguments args, UIInputDelegater dg);
int HCityList(UIArguments args, UIInputDelegater dg);

int HRouteMgr(UIArguments args, UIInputDelegater dg);
int HAskRouteMgr(UIArguments args, UIInputDelegater dg);
int HRouteAdd(UIArguments args, UIInputDelegater dg);
int HRouteDelete(UIArguments args, UIInputDelegater dg);
int HRouteList(UIArguments args, UIInputDelegater dg);

int HAdvice(UIArguments args, UIInputDelegater dg);
int HAskAdvice(UIArguments args, UIInputDelegater dg);

int HAskLprice(UIArguments args, UIInputDelegater dg);
int HAskLtime(UIArguments args, UIInputDelegater dg);
int HAskLtrans(UIArguments args, UIInputDelegater dg);

class HChoiceDelegater {
private:
    std::map<int, std::function<void()> > func;
    std::function<void()> ferr;
    bool hasFault = false;
    UINormal *prevUI;

    void DEFAULT_FAULT();
    void execFault();
public:
    HChoiceDelegater(UINormal *prevUI): prevUI(prevUI) {}
    void bind(int x, std::function<void()> f);
    void fault(std::function<void()> f);
    void act(UIArguments args, UIInputDelegater dg);
};