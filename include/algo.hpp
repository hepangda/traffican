#pragma once
#include"utils.h"
#include<vector>
#include<algorithm>
#include<queue>
#include<iostream>
#include"io.h"

struct Path {
    long tp, power, tm;
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
            return r.ends;
        }
    };

    template<typename PADD>
    static Path dijkstra(long fromID, long toID, Time tm)
    {
        struct PCMP {
            bool operator()(const Path &a, const Path &b)
            {
                return a.power > b.power;
            }
        };
        std::priority_queue<Path, std::vector<Path>, PCMP> Q;
        PADD padd;
        Q.push({fromID, 0, tm, {}});

        while (!Q.empty()) {
            auto u = Q.top(); Q.pop();
            if (u.tp == toID) {
                return u;
            }

            auto v = getRouteByStart(u.tp, u.tm);
            for (auto &i: v) {
                u.travel.push_back(i);
                Q.push({i.to, padd(u.power, i), i.ends, u.travel});
                u.travel.pop_back();
            }
        }

        return {-1, -1, {}};
    }

    static std::vector<Route> getRouteByStart(long id, Time tm)
    {
        std::vector<Route> ret;
        for (auto &i: IORoute) {
            if (i.from == id)
                ret.push_back(i);
        }
        return ret;
    }
};