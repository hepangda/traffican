#include"utils.h"

long cityidMaker = 0;

Time timeAdd(const Time a, const Time b)
{
    int h1 = a / 10000, h2 = b / 10000,
        m1 = (a / 100) % 100, m2 = (b / 100) % 100,
        s1 = a % 100, s2 = b % 100;
    return (h1 + h2) * 10000 + (m1 + m2) * 100 + (s1 + s2);
}

Time timeMinus(const Time a, const Time b)
{
    int h1 = a / 10000, h2 = b / 10000,
        m1 = (a / 100) % 100, m2 = (b / 100) % 100,
        s1 = a % 100, s2 = b % 100;
    return (h1 - h2) * 10000 + (m1 - m2) * 100 + (s1 - s2);
}