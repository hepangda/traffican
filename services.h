#pragma once
#include"utils.h"

class Service {
public:
    static const int SUCCESS = 0;
    static const int NOT_FOUND = 1;

    static int addCity(City x);
    static City *findCity(std::string name);
    static int editCity(std::string name, City info);
    static int deleteCity(std::string name);
};