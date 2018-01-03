#include<algorithm>
#include<queue>
#include"algo.h"
#include"io.h"

using namespace std;

vector<Route> Algorithm::getRouteByStart(long id)
{
    vector<Route> ret;
    for (auto &i: IORoute) {
        if (i.starts == id)
            ret.push_back(i);
    }
    return ret;
}

template<typename PADD>
Path Algorithm::dijkstra(long fromID, long toID)
{
    struct PCMP {
        bool operator()(const Path &a, const Path &b)
        {
            return a.power > b.power;
        }
    };
    priority_queue<Path, vector<Path>, PCMP> Q;
    PADD padd;
    Q.push({fromID, 0, {}});

    while (!Q.empty()) {
        auto u = Q.top(); Q.pop();
        if (u.tp == toID) {
            return u;
        }

        auto v = getRouteByStart(u.tp);
        for (auto &i: v) {
            u.travel.push_back(i);
            Q.push({i.to, padd(u.power, i), u.travel});
            u.travel.pop_back();
        }
    }

    return {-1, -1, {}};
}