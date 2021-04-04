#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <x/time.h>

char buffer[8196];

static void init(void)
{
    srandom(time(0));

    for(int i = 0; i < 8192; i++)
    {
        buffer[i] = (random() % 26) + 97;
    }
    buffer[8192] = 0;
}

static void copy(char * __restrict__ dest, char * __restrict__ src, int n, int out)
{
    register unsigned long * desti = (unsigned long *) dest;
    register unsigned long * srci = (unsigned long *) src;

    register unsigned long to = n / 16;
    
    // register __int128_t * desti = (__int128_t *) dest;
    // register __int128_t * srci = (__int128_t *) src;

    xtime start = xtimeget();
    while(to--)
    {
        *(desti + to) = *(srci + to);
//        *(desti + n) = *(srci + n);
    }
    // for(xint64 i = 0; i < n; i++)
    // {
    //     *(desti + i) = *(srci + i);
    // }
    xtime end = xtimeget();

    xtime diff = xtimediff(xaddressof(end), xaddressof(start));
    if(out)
    {
        printf("%ld.%09ld\n", diff.second, diff.nanosecond);
    }
}

static void memcopy(char * __restrict__ dest, char * __restrict__ src, int n)
{
    xtime start = xtimeget();

    memcpy(dest, src, n);

    xtime end = xtimeget();
    xtime diff = xtimediff(xaddressof(end), xaddressof(start));

    printf("%ld.%09ld\n", diff.second, diff.nanosecond);
}

char dest[10000];
char dest2[10000];

int main(int argc, char ** argv)
{

    memset(dest2, 0, 8192);
    memcpy(dest2, buffer, 8192);

    init();

    for(int i = 0; i < 32; i++)
    {
        // memset(dest2, 0, 8192);
        memcopy(dest2, buffer, 8192);
        
        // if(memcmp(dest2, buffer, 8192) != 0)
        // {
        //     printf("fail\n");
        // }
    }

    printf("===========================\n");

    copy(dest, buffer, 8192, 0);

    for(int i = 0; i < 32; i++)
    {
        // memset(dest, 0, 8192);
        copy(dest, buffer, 8192, 1);
        // if(memcmp(dest, buffer, 8192) != 0)
        // {
        //     printf("fail\n");
        // }

        // printf("===========================\n");





    }



    return 0;
}