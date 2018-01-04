#include"handler.h"

UIQuery UFAskMainmenu(Handlers::askMainmenu, UIInputDelegater::generic,
{
"   > 请选择"
});

UINormal UFMainmenu(Handlers::mainmenu, UIInputDelegater::generic,
{
"  ================== 欢迎使用Traffican ==================  ",
"                   1. 城市信息管理",
"                   2. 交通线路管理",
"                   3. 获得出行建议",
"                   4. 退出咨询系统",
"  ======================================================  "
});

UINormal UFExit(Handlers::exit, UIInputDelegater::generic,
{
"\n",
"  ======================================================  ",
"",
"                       感谢使用！",
"",
"  ======================================================  "
});

UINormal UFCityMgr(Handlers::cityMgr, UIInputDelegater::generic,
{
"  ==================== 城市信息管理 =====================  ",
"                   1. 列出现有城市",
"                   2. 增加新的城市",
"                   3. 修改城市介绍",
"                   4. 删除已有城市",
"                   5. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskCityMgr(Handlers::askCityMgr, UIInputDelegater::generic,
{
"   > 请选择"
});

UIQuery UFCityAdd(Handlers::cityAdd, UIInputDelegater::generic,
{
"   > 城市名",
"   > 城市介绍"
});

UIQuery UFCityEdit(Handlers::cityEdit, UIInputDelegater::generic,
{
"   > 要修改的城市名",
"   > 城市介绍"
});

UIQuery UFCityDelete(Handlers::cityDelete, UIInputDelegater::generic,
{
"   > 城市名"
});

UIForm UFCityList(Handlers::cityList, UIInputDelegater::generic);

UINormal UFRouteMgr(Handlers::routeMgr, UIInputDelegater::generic,
{
"  ==================== 交通线路管理 =====================  ",
"                   1. 列出现有线路",
"                   2. 新增一条线路",
"                   3. 删除已有线路",
"                   4. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskRouteMgr(Handlers::askRouteMgr, UIInputDelegater::generic,
{
"   > 请选择"
});

UIQuery UFRouteAdd(Handlers::routeAdd, UIInputDelegater::generic,
{
"   > 起始城市",
"   > 终点城市",
"   > 类型(火车/飞机/高铁)",
"   > 开始时间(时:分:秒)",
"   > 结束时间(时:分:秒)",
"   > 票价(元)"
});

UIQuery UFRouteDelete(Handlers::routeDelete, UIInputDelegater::generic,
{
"   > 路线ID"
});

UIForm UFRouteList(Handlers::routeList, UIInputDelegater::generic);

UINormal UFAdvice(Handlers::advice, UIInputDelegater::generic,
{
"  ==================== 出行建议系统 =====================  ",
"             请选择建议策略：",
"                   1. 最少用时到达",
"                   2. 最省费用到达",
"                   3. 中转最少到达",
"                   4. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskAdvice(Handlers::askAdvice, UIInputDelegater::generic,
{
"   > 请选择"
});

UIQuery UFAskLtime(Handlers::askLtime, UIInputDelegater::generic,
{
"   > 起点",
"   > 终点",
"   > 出发时间(时:分:秒)"
});

UIQuery UFAskLprice(Handlers::askLprice, UIInputDelegater::generic,
{
"   > 起点",
"   > 终点",
"   > 出发时间(时:分:秒)"
});

UIQuery UFAskLtrans(Handlers::askLtrans, UIInputDelegater::generic,
{
"   > 起点",
"   > 终点",
"   > 出发时间(时:分:秒)"
});