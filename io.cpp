#include"utils.h"
#include"io.h"
#include<vector>
#include<cstdio>
using namespace std;

extern long idMaker;
extern long cityidMaker;
vector<City> IOCity;
vector<Route> IORoute;
const char IO::CityFile[] = "data/City.dat";
const char IO::RouteFile[] = "data/Route.dat";

int IO::WriteCity()
{
    auto writeOne = [](FILE *fp, City &x)
    {
        int sa = x.name.size(), sb = x.intro.size();
        fwrite(&sa, sizeof(int), 1, fp);
        fwrite(&sb, sizeof(int), 1, fp);
        fwrite(x.name.data(), sa, 1, fp);
        fwrite(x.intro.data(), sb, 1, fp);
        fwrite(&x.id, sizeof(int), 1, fp);
    };

    FILE *fp = fopen(CityFile, "wb+");
    int size = IOCity.size();
    fwrite(&cityidMaker, sizeof(long), 1, fp);
    fwrite(&size, sizeof(int), 1, fp);
    for (auto &i: IOCity) {
        writeOne(fp, i);
    }

    fflush(fp);
    fclose(fp);
    return 0;
}

int IO::WriteRoute()
{
    auto writeOne = [](FILE *fp, Route &x)
    {
        fwrite(&x, sizeof(Route), 1, fp);
    };

    FILE *fp = fopen(RouteFile, "wb+");
    int size = IORoute.size();
    fwrite(&idMaker, sizeof(long), 1, fp);
    fwrite(&size, sizeof(int), 1, fp);
    for (auto &i: IORoute) {
        writeOne(fp, i);
    }

    fflush(fp);
    fclose(fp);
    return 0;
}

int IO::WriteAll()
{
    WriteCity();
    WriteRoute();
}

int IO::ReadAll()
{
    auto readOneCity = [](FILE *fp) -> City 
    {
        City ret;
        int sa, sb;
        fread(&sa, sizeof(int), 1, fp);
        fread(&sb, sizeof(int), 1, fp);
        char *bufa = new char[sa + 1],
             *bufb = new char[sb + 1];
        fread(bufa, sa, 1, fp);
        fread(bufb, sb, 1, fp);
        bufa[sa] = '\0';
        bufb[sb] = '\0';
        ret.name = bufa;
        ret.intro = bufb;
        delete[] bufa;
        delete[] bufb;
        fread(&ret.id, sizeof(int), 1, fp);

        return ret;
    };

    auto readOneRoute = [](FILE *fp) -> Route
    {
        Route ret;
        fread(&ret, sizeof(Route), 1, fp);
        return ret;
    };

    FILE *fc = fopen(CityFile, "rb");
    if (fc != nullptr) {
        int sc;
        fread(&cityidMaker, sizeof(long), 1, fc);
        fread(&sc, sizeof(int), 1, fc);
        for (int i = 0; i < sc; i ++)
            IOCity.push_back(readOneCity(fc));
        fclose(fc);
    }

    FILE *fr = fopen(RouteFile, "rb");
    if (fr != nullptr) {
        int sr;
        fread(&idMaker, sizeof(long), 1, fr);
        fread(&sr, sizeof(int), 1, fr);

        for (int i = 0; i < sr; i++)
            IORoute.push_back(readOneRoute(fr));
        fclose(fr);
    }
    return 0;
}