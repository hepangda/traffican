#pragma once
#include"utils.h"
#include"ui.h"
#include<vector>
#include<string>

class Service {
public:
    static const int SUCCESS = 0;
    static const int NOT_FOUND = 1;
    static const int EXISTED = 2;
    static const int ERROR_MSG = 3;

    static int addCity(City x);
    static std::vector<City>::iterator findCity(std::string name);
    static int editCity(City info);
    static int deleteCity(std::string name);
    static int loadCity(UIForm &form);

    static int addRoute(RouteRequest x);
    static std::vector<Route>::iterator findRoute(long id);
    static int deleteRoute(long id);
    static int loadRoute(UIForm &form);

    static long cityIDFromString(std::string name);
    static std::string cityStringFromID(long id);
    static int typeIDFromString(std::string name);
    static std::string typeStringFromID(int id);
    static Time timeFromString(std::string ts);
    static std::string timeFromTimet(Time tm);
};