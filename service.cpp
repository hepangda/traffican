#include"services.h"
#include"io.h"

using namespace std;

int Service::addCity(City x)
{
    IOCity.push_back(x);
    return SUCCESS;
}

City *Service::findCity(string name)
{
    for (auto &i: IOCity) {
        if (i.name == name)
            return &i;
    }
    return nullptr;
}

int Service::editCity(string name, City info)
{
    City *p = findCity(name);
    if (p == nullptr)
        return NOT_FOUND;
    *p = info;
    return SUCCESS;
}