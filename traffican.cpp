#include"utils.h"
#include"forums.h"
#include"handler.h"
using namespace std;
int main(int argc, char *argv[])
{
    // UIGlobal::clear();
    // UIGlobal::set(UFMainmenu);
    // UIGlobal::main();
    UIForm form(HMainmenu, genericDelegater);
    vector<int> w = { 10, 10, 10 };
    vector<string> t = {"aa", "bbb", "ccccc"};
    vector<vector<string> > c= {
        {"1","a", "A"},
        {"2","b","B"}
    };
    form.put(w,t,c);
    form.act(cout);
    return 0;
}