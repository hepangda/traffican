#pragma once
#include"utils.h"
#include<vector>

class Service {
public:
    static const int SUCCESS = 0;
    static const int NOT_FOUND = 1;

    static int addCity(City x);
    static std::vector<City>::iterator findCity(std::string name);
    static int editCity(std::string name, City info);
    static int deleteCity(std::string name);

    static int addRoute(Route x);
    static std::vector<Route>::iterator findRoute();
    static int editRoute();
    static int deleteRoute();
};