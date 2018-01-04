#include"utils.h"
#include"forums.h"
#include"handler.h"
#include"io.h"
using namespace std;
int main(int argc, char *argv[])
{
    IO::ReadAll();
    UIGlobal::clear();
    UIGlobal::set(UFMainmenu);
    UIGlobal::main();
    IO::WriteAll();
    return 0;
}