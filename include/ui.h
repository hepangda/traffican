#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<map>
#include<functional>

class UIInputDelegater {
private:
    std::map<int, std::string> store;
    long iter = -1000000;
    void erase(long id);

    template<typename E, typename T, typename F>
    E getAny(long id);

public:
    struct Value {
        bool vaild = false;
        Value(bool vaild): vaild(vaild) {}
    };

    struct Long: public Value {
        Long(bool vaild, long val): Value(vaild), val(val) {}
        long val;
    };

    struct Double: public Value {
        Double(bool vaild, double val): Value(vaild), val(val) {}
        double val;
    };

    struct String: public Value {
        String(bool vaild, std::string val): Value(vaild), val(val) {}
        std::string val;
    };

    static UIInputDelegater generic;
    long delegate(std::string content);
    Long getInt(long id);
    String getString(long id);
    Double getDouble(long id);
};

typedef std::vector<int> UIArguments;
typedef int (*UIHandler)(UIArguments, UIInputDelegater);
typedef std::vector<std::string> UIPrompt;

class UINormal {
protected:
    UIPrompt prompts;
    UIHandler handler;
    UIInputDelegater delegater;
public:
    static const std::string CLEAR;
    UINormal(UIHandler handler, UIInputDelegater delegater, UIPrompt prompts):
        handler(handler), delegater(delegater), prompts(prompts) {}
    virtual void act(std::ostream &os);
};

class UIQuery: public UINormal {
public:
    UIQuery(UIHandler handler, UIInputDelegater delegater, UIPrompt prompts): 
        UINormal(handler, delegater, prompts) {}
    virtual void act(std::ostream &os);
};

class UIForm: public UINormal {
private:
    std::vector<int> widths;
    std::vector<std::string> names;
    std::vector<std::vector<std::string> > content;
    bool set = false;
public:
    UIForm(UIHandler handler, UIInputDelegater delegater): 
        UINormal(handler, delegater, UIPrompt{}) {}
    void put(std::vector<int> widths, std::vector<std::string> names, std::vector<std::vector<std::string> > content);
    virtual void act(std::ostream &os);
};

class UIGlobal {
private:
    static bool watchdog;
    static UINormal *nextUI;
public:
    static void main();
    static void abort();
    static void clear();
    static void clear(std::function<void()> f);
    static void set(UINormal &ui);
    static void set(UINormal *ui);
    static void setAndClear(UINormal &ui);
    static void setAndClear(UINormal &ui, std::function<void()> f);
};