#include <x/eva.h>

int main(int argc, char ** argv)
{
    xevaconfigloginit("/novemberizing", xlogtype_all);

    return xevarun(argc, argv);
}
