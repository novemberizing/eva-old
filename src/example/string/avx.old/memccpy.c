/**

memccpy
=======

> copy bytes in memory.

The `memccpy()` function shall copy bytes from memory area s2 into s1,
stopping after the first occurrence of byte c (converted to an unsigned char) is copied,
or after n bytes are copied, whichever comes first.

If copying takes place between objects that overlap, the behavior is undefined.

## Synopsis

```c
#include <string.h>

void *memccpy(void *restrict s1, const void *restrict s2, int c, size_t n);
```

## Return

The memccpy() function shall return a pointer to the byte after the copy of c in s1,
or a null pointer if c was not found in the first n bytes of s2.

## Errors

No errors are defined.

## Application usage

The `memccpy()` function does not check for the overflow of the receiving memory area.


$ gcc -Wall -Wextra -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations  -fsanitize=undefined -mavx memccpy.c

 */

#include "avx.h"

char destination[65536 + 256];

#define xcheckzero(x)    ((x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL)

static void * xmemorycopy_until(void * __restrict destination, const void * __restrict source, int c, unsigned long n)
{
    register __m256i * d = (__m256i *) destination;
    register const __m256i * s = (const __m256i *) source;
    register __m256i temp;
    register xvector256 match;

    unsigned long v = c;
    v |= v << 8;
    v |= v << 16;
    v |= v << 32;
    
    // __m256i v256 = _mm256_set_epi64x(v, v, v, v);
    printf("%p => \n", s);
    printf("%016lx\n", v);
    for(unsigned long i = 32; i <= n; i = i + 32)
    {
        temp = _mm256_loadu_si256(s++);
        match.i256 = (((temp & v) - v) & 0xFFFFFFFFFFFFFFFFUL);
        match.i256 = (temp & v);
        printf("%016lx %016lx %016lx %016lx\n", match.u64[0], match.u64[1], match.u64[2], match.u64[3]);
        if(match.u64[0] || match.u64[1] || match.u64[2] || match.u64[3])
        {
            printf("match %p\n", s);
            break;
        }
        break;
        _mm256_store_si256(d++, temp);
        // d->i256 = ;
        // if xcheckzero ... 
        // xvector256 v = { .i256 = _mm256_loadu_si256(src) };
    }
    return 0;

    // for(unsigned long i = 32; i <= n; i = i + 32)
    // {
    //     xvector256 v = { .i256 = _mm256_loadu_si256(src) };

    //     v.u64  = xcheckzero(v.u64);
    //     if(v.u64[0] || v.u64[1] || v.u64[2] || v.u64[3])
    //     {
    //         register char * c = &(v.c8[0]);
    //         while(!*c){ ++c; }
    //         return ((const char *) data) - s + (c - &(v.c8[0]));
    //     }

    //     _mm256_store_si256(dest++, _mm256_loadu_si256(src++));
    // }

    // n = n % 32;
    // unsigned long * destu64 = (unsigned long *) dest;
    // unsigned long * srcu64 = (unsigned long *) src;
    // for(unsigned long i = 0; i < (n / 8); i++)
    // {
    //     *((unsigned long *) destu64++) = *((unsigned long *) srcu64++);
    // }

    // n = n % 8;
    // char * o = (char *) destu64;
    // char * i = (char *) srcu64;

    // while(n--)
    // {
    //     *(o++) = *(i++);
    // }
    // return destination;
}

void experiment_memccpy(const char * title)
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

        char * n = memccpy(destination, s, 0, 65536 + 128);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        // if(memcmp(destination, s, reallen[index]) || (unsigned long) (n - (char *) destination) != reallen[index] + 1)
        // {
        //     printf("assertion\n");
        //     exit(-1);
        // }
        printf("%p %ld %ld.%09ld\r", n, reallen[index], diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    printf("                                                      \r");

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void experiment_xmemorycopy_until(const char * title)
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

        char * n = xmemorycopy_until(destination, s, 0, 65536 + 128);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        // if(memcmp(destination, s, reallen[index]) || (unsigned long) (n - (char *) destination) != reallen[index] + 1)
        // {
        //     printf("assertion\n");
        //     exit(-1);
        // }
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
    (void)(argc);
    (void)(argv);

    init();

    experiment_memccpy          ("memccpy           => ");
    experiment_xmemorycopy_until("xmemorycopy_until => ");

    // printf("hello world\n");
    // char buffer[65536 + 128];
    // char * ret = memccpy(buffer, experimentstr[0], 'a', 65536 + 128);
    // printf("ret => %p\n", ret);
    // printf("experimentstr[0] => %p\n", experimentstr[0]);
    // printf("buffer => %p\n", buffer);
    // printf("buffer => %s\n", buffer);
    // printf("%d\n", *ret);

    return 0;
}