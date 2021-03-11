#include <x/log.h>

int main(int argc, char ** argv)
{
    xlogpath_set("/home/hyunsik/benchmark");
    xlogmask_set(xlogtype_verbose);

    int total = 10000000;
    for(int i = 0; i < total; i++)
    {
        xlogverbose("hello world");
    }
    
    return 0;
}
