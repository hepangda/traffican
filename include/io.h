#pragma once

#include<vector>
#include"utils.h"
extern std::vector<City> IOCity;
extern std::vector<Route> IORoute;

class IO {
public:
    static const char CityFile[];
    static const char RouteFile[];
    static int WriteCity();
    static int WriteRoute();
    static int WriteAll();
    static int ReadAll();
};