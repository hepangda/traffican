#pragma once
#include"utils.h"
#include<vector>

struct Path {
    long tp, power;
    std::vector<Route> travel;
};

class Algorithm {
public:
    struct LessTrans {
        long operator()(long ori, Route &r)
        {
            return ori + 1;
        }
    };

    struct LessPrice {
        long operator()(long ori, Route &r)
        {
            return ori + r.price;
        }
    };

    struct LessTime {
        long operator()(long ori, Route &r)
        {
            return timeAdd(ori, timeMinus(r.ends, r.starts));
        }
    };

    template<typename PADD>
    static Path dijkstra(long fromID, long toID);
    static std::vector<Route> getRouteByStart(long id);
};