#include<iostream>
#include<iomanip>
#include<functional>
#include"forums.h"
using namespace std;

bool UIGlobal::watchdog = true;
UINormal *UIGlobal::nextUI = nullptr;
const std::string UINormal::CLEAR = "\n";

void UIGlobal::clear()
{
#ifdef WIN32
    system("cls");
#endif // WIN32
#ifdef linux
    system("clear");
#endif // linux
}

void UIGlobal::clear(function<void()> f)
{
    clear();
    f();
}

void UIGlobal::abort() 
{
    watchdog = false;
}

void UIGlobal::main()
{
    while (watchdog) {
        nextUI->act(cout);
    }
}

void UIGlobal::setAndClear(UINormal &ui)
{
    clear();
    set(ui);
}

void UIGlobal::set(UINormal *ui)
{
    nextUI = ui;
}

void UIGlobal::set(UINormal &ui)
{
    nextUI = &ui;
}

void UIGlobal::setAndClear(UINormal &ui, std::function<void()> f)
{
    clear(f);
    set(ui);
}


void UIInputDelegater::erase(long id)
{
    auto it = store.find(id);
    store.erase(it);
}

long UIInputDelegater::delegate(std::string content)
{
    store[iter] = content;
    return iter++;
}

template<typename E, typename T, typename F>
E UIInputDelegater::getAny(long id)
{
    F trans;

    std::string ori = store[id];
    try {
        T val = trans(ori);
        erase(id);
        return { true, val };
    } catch (exception ex) {
        return { false, 0 };
    }
}

#define STOX(x, type, expr) struct STO##x { type operator()(std::string st) { return expr; } };

UIInputDelegater::Long UIInputDelegater::getInt(long id)
{
    STOX(L, long, stol(st));
    return getAny<Long, long, STOL>(id);
}

UIInputDelegater::String UIInputDelegater::getString(long id)
{
    STOX(S, std::string, st);
    return getAny<String, std::string, STOS >(id);
}

UIInputDelegater::Double UIInputDelegater::getDouble(long id)
{
    STOX(D, double, stod(st));
    return getAny<Double, double, STOD>(id);
}

#undef STOX

void UINormal::act(std::ostream &os)
{
    for (auto i: prompts) {
        if (i == CLEAR)
            UIGlobal::clear();
        else
            os << i << endl;
    }

    handler(vector<int>{}, delegater);
}

void UIQuery::act(std::ostream &os)
{
    vector<int> args;
    for (auto i = 0u; i < prompts.size(); i++) {
        os << prompts[i] << ": ";
        string in;
        cin >> in;
        args.push_back(delegater.delegate(in));
    }

    handler(args, delegater);
}

void UIForm::put(vector<int> widths, vector<string> names, vector<vector<string> > content)
{
    this->widths = widths;
    this->names = names;
    this->content = content;
    set = true;
}

void UIForm::act(std::ostream &os)
{
    handler(vector<int>{}, delegater);
    if (!set)
        return;

    auto sepline = [](int allen)
    {
        cout << "  ";
        for (int i = 0; i < allen; i++)
            cout << "=";
        cout << endl;
    };

    int allen = 0;
    for (auto i: widths) {
        allen += i + 1;
    }
    sepline(allen);
    cout << "  ";
    for (int i = 0; i < widths.size(); i++) {
        cout << setw(widths[i]) << left << names[i] << " ";
    }
    cout << endl;
    sepline(allen);
    for (int i = 0; i < content.size(); i++) {
        cout << "  ";
        for (int j = 0; j < widths.size(); j++) {
            cout << setw(widths[j]) << left << content[i][j] << " ";
        }
        cout << endl;
    }
    sepline(allen);
    cout << endl << endl;
}