#pragma once
#include<string>

struct City {
    std::string name;
    std::string intro;
    long id;
};

struct Route {
    long from, to;
    int type, price;
    time_t starts, ends;
};