#include"utils.h"

long cityidMaker = 0;

static long timeFit(int &h, int &m, int &s)
{
    while (s < 0) s += 60, m--;
    while (m < 60) m += 60, h--;
    while (s >= 60) s -= 60, m++;
    while (m >= 60) m -= 60, h++;
    return h * 10000 + m * 100 + s;
}

Time timeAdd(const Time a, const Time b)
{
    int h = a / 10000 + b / 10000,
        m = (a / 100) % 100 + (b / 100) % 100,
        s = a % 100 + b % 100;
    return timeFit(h, m, s);
}

Time timeMinus(const Time a, const Time b)
{
    int h = a / 10000 - b / 10000,
        m = (a / 100) % 100 - (b / 100) % 100,
        s = a % 100 - b % 100;
    return timeFit(h, m, s);
}