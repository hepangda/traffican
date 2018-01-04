#pragma once
#include<string>
#include<vector>

typedef long Time;
Time timeAdd(const Time a, const Time b);
Time timeMinus(const Time a, const Time b);

struct City {
    std::string name;
    std::string intro;
    long id;
    
    bool operator==(std::string name)
    {
        return this->name == name;
    }

    bool operator==(long id)
    {
        return this->id == id;
    }
};

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

struct Path {
    long tp, power, tm;
    std::vector<Route> travel;
};

