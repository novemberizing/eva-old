#include <stdio.h>

#include <x/string.h>

int main(int argc, char ** argv)
{
    xuint64 ret = xstringtouint64("1024", 4);
    printf("%lu\n", ret);
    return 0;
}
