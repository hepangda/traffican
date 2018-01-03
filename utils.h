#pragma once
#include<string>

struct City {
    std::string name;
    std::string intro;
    long id;
    static long idMaker;
    bool operator==(std::string name)
    {
        return this->name == name;
    }

    bool operator==(long id)
    {
        return this->id == id;
    }
};

typedef long Time;

struct Route {
    long from, to, price;
    int type;
    Time starts, ends;
    long id;
    bool operator==(long id)
    {
        return this->id == id;
    }
};

struct RouteRequest {
    std::string from, to, type, starts, ends;
    long price;
};

Time timeAdd(const Time a, const Time b);
Time timeMinus(const Time a, const Time b);