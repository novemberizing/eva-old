/**
https://pubs.opengroup.org/onlinepubs/009696899/functions/memcpy.html

memcpy - copy bytes in memory

```
#include <string.h>

void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
```

The functionality described on this reference page is aligned with the ISO C standard.
Any conflict between the requirements described here and the ISO C standard is unintentional.
This volume of IEEE Std 1003.1-2001 defers to the ISO C standard.

The memcpy() function shall copy n bytes from the object pointed to by s2 into the object pointed to by s1. If copying takes place between objects that overlap, the behavior is undefined.

Return

The memcpy() function shall return s1; no return value is reserved to indicate an error.

Error

No errors are defined.

APPLICATION USAGE

The memcpy() function does not check for the overflow of the receiving memory area.


gcc -O2 -mavx memcpy.c

O3 보다 O2 가 체감적으로 더 빠른 것 같다.

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#include "./avx.h"

typedef unsigned long xvector64x4 __attribute__ ((vector_size(32)));
typedef char          xvector8x32 __attribute__ ((vector_size(32)));


union xvector256
{
    __m256i     i256;
    xvector64x4 u64;
    xvector8x32 c8;
};

typedef union xvector256 xvector256;


static void * xmemorycopy(void * __restrict destination, const void * __restrict source, unsigned long n)
{
    register __m256i * dest = (__m256i *) destination;
    register const __m256i * src = (const __m256i *) source;
    for(unsigned long i = 32; i <= n; i = i + 32)
    {
        _mm256_store_si256(dest++, _mm256_loadu_si256(src++));
    }

    n = n % 32;
    unsigned long * destu64 = (unsigned long *) dest;
    unsigned long * srcu64 = (unsigned long *) src;
    for(unsigned long i = 0; i < (n / 8); i++)
    {
        *((unsigned long *) destu64++) = *((unsigned long *) srcu64++);
    }

    n = n % 8;
    char * o = (char *) destu64;
    char * i = (char *) srcu64;

    while(n--)
    {
        *(o++) = *(i++);
    }
    return destination;
}

char destination[65536 + 128];

void experiment_xmemorycopy(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        memset(destination, 0, 65536 + 128);
        int index = randomuint(experimentalstrcnt);
        char * s = experimentalstr[index];
        clock_gettime(CLOCK_REALTIME, &start);

        char * n = xmemorycopy(destination, s, reallen[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        if(memcmp(destination, s, reallen[index]))
        {
            printf("assertion\n");
            exit(-1);
        }
        printf("%p %ld %ld.%09ld\r", n, reallen[index], diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    printf("                                                      \r");

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void experiment_memcpy(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        memset(destination, 0, 65536 + 128);
        int index = randomuint(experimentalstrcnt);
        char * s = experimentalstr[index];
        clock_gettime(CLOCK_REALTIME, &start);

        char * n = memcpy(destination, s, reallen[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        if(memcmp(destination, s, reallen[index]))
        {
            printf("assertion\n");
            exit(-1);
        }
        printf("%p %ld %ld.%09ld\r", n, reallen[index], diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    printf("                                                      \r");

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

int main(int argc, char ** argv)
{
    init();
    printf("hello world => memcpy\n");
    experiment_xmemorycopy("xmemorycopy => ");
    experiment_memcpy     ("memcpy      => ");
    
    return 0;
}
