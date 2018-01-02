#include"handler.h"

UIInputDelegater genericDelegater;

UIQuery UFAskMainmenu(HAskMainmenu, genericDelegater,
{
"   > 请选择"
});

UINormal UFMainmenu(HMainmenu, genericDelegater,
{
"  ================== 欢迎使用Traffican ==================  ",
"                   1. 城市信息管理",
"                   2. 交通线路管理",
"                   3. 获得出行建议",
"                   4. 退出咨询系统",
"  ======================================================  "
});

UINormal UFExit(HExit, genericDelegater,
{
"\n",
"  ======================================================  ",
"",
"                       感谢使用！",
"",
"  ======================================================  "
});

UINormal UFCityMgr(HCityMgr, genericDelegater,
{
"  ==================== 城市信息管理 =====================  ",
"                   1. 列出现有城市",
"                   2. 增加新的城市",
"                   3. 修改已有城市",
"                   4. 删除已有城市",
"                   5. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskCityMgr(HAskCityMgr, genericDelegater,
{
"   > 请选择"
});

UIQuery UFCityAdd(HCityAdd, genericDelegater,
{
"   > 城市名",
"   > 城市介绍"
});

UIQuery UFCityEdit(HCityEdit, genericDelegater,
{
"   > 城市名",
"   > 城市介绍"
});

UIQuery UFCityDelete(HCityDelete, genericDelegater,
{
"   > 城市名"
});

UINormal UFRouteMgr(HRouteMgr, genericDelegater,
{
"  ==================== 交通线路管理 =====================  ",
"                   1. 列出现有线路",
"                   2. 新增一条线路",
"                   3. 修改某条线路",
"                   4. 删除已有线路",
"                   5. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskRouteMgr(HAskRouteMgr, genericDelegater,
{
"   > 请选择"
});

UINormal UFAdvice(HAdvice, genericDelegater,
{
"  ==================== 出行建议系统 =====================  ",
"             请选择建议策略：",
"                   1. 最少用时到达",
"                   2. 最省费用到达",
"                   3. 中转最少到达",
"                   4. 返回上级菜单",
"  ======================================================  "
});

UIQuery UFAskAdvice(HAskAdvice, genericDelegater,
{
"   > 请选择"
});
