#ifndef   __EXAMPLE_STRING_AVX__
#define   __EXAMPLE_STRING_AVX__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
#include <string.h>

union xvector256;
union xvector512;

typedef unsigned long xvector64x4 __attribute__ ((vector_size(32)));
typedef unsigned char xvector8x32 __attribute__ ((vector_size(32)));

typedef unsigned long xvector64x8 __attribute__ ((vector_size(64)));
typedef unsigned char xvector8x64 __attribute__ ((vector_size(64)));
typedef union xvector512 xvector512;

union xvector256
{
    __m256i     i256;
    xvector64x4 u64;
    xvector8x32 u8;
};

union xvector512
{
    __m512i     i512;
    __m512d     d512;
    xvector64x8 u64;
    xvector8x64 u8;
};

static const int experimentmax = 65536;
static const int experimentalstrcnt = 1024;

static char experimentalstr[1024][65536 + 256];
static unsigned long reallen[1024];

#define timespec_diff(x, y, out) do {                   \
    (out)->tv_sec = (x)->tv_sec - (y)->tv_sec;          \
    (out)->tv_nsec = (x)->tv_nsec - (y)->tv_nsec;       \
    if((out)->tv_nsec < 0) {                            \
        (out)->tv_sec = (out)->tv_sec - 1;              \
        (out)->tv_nsec = 1000000000 + (out)->tv_nsec;   \
    }                                                   \
} while(0)

#define randomstrget()      ((((unsigned long) random()) % 26) + 97)
#define randomuint(max)     (int) (((unsigned long) random()) % max)

static inline void init(void)
{
    srandom(time((void *) 0));

    for(int i = 0; i < experimentalstrcnt; i++)
    {
        int n = randomuint(64);
        reallen[i] = 65536 + n;
        for(unsigned long j = 0; j < reallen[i]; j++)
        {
            experimentalstr[i][j] = ((((unsigned long) random()) % 26) + 97);
        }
        experimentalstr[i][reallen[i]] = 0;
        for(unsigned long j = reallen[i] + 1; j < reallen[i]; j++)
        {
            experimentalstr[i][j] = '!';
        }
    }
}

#define timespecdiff(x, y, z) do {                  \
    (z)->tv_sec = (x)->tv_sec - (y)->tv_sec;        \
    (z)->tv_nsec = (x)->tv_nsec - (y)->tv_nsec;     \
    if((z)->tv_nsec < 0)                            \
    {                                               \
        (z)->tv_nsec = 1000000000 + (z)->tv_nsec;   \
        (z)->tv_sec = (z)->tv_sec - 1;              \
    }                                               \
} while(0)

#define timespecmax(x, y, z) do {                   \
    if((x)->tv_sec > (y)->tv_sec)                   \
    {                                               \
        (z)->tv_sec = (x)->tv_sec;                  \
        (z)->tv_nsec = (x)->tv_nsec;                \
    }                                               \
    else if((x)->tv_sec < (y)->tv_sec)              \
    {                                               \
        (z)->tv_sec = (y)->tv_sec;                  \
        (z)->tv_nsec = (y)->tv_nsec;                \
    }                                               \
    else                                            \
    {                                               \
        if((x)->tv_nsec >= (y)->tv_nsec)            \
        {                                           \
            (z)->tv_sec = (x)->tv_sec;              \
            (z)->tv_nsec = (x)->tv_nsec;            \
        }                                           \
        else                                        \
        {                                           \
            (z)->tv_sec = (y)->tv_sec;              \
            (z)->tv_nsec = (y)->tv_nsec;            \
        }                                           \
    }                                               \
} while(0)

#define timespecmin(x, y, z) do {                   \
    if((x)->tv_sec < (y)->tv_sec)                   \
    {                                               \
        (z)->tv_sec = (x)->tv_sec;                  \
        (z)->tv_nsec = (x)->tv_nsec;                \
    }                                               \
    else if((x)->tv_sec > (y)->tv_sec)              \
    {                                               \
        (z)->tv_sec = (y)->tv_sec;                  \
        (z)->tv_nsec = (y)->tv_nsec;                \
    }                                               \
    else                                            \
    {                                               \
        if((x)->tv_nsec <= (y)->tv_nsec)            \
        {                                           \
            (z)->tv_sec = (x)->tv_sec;              \
            (z)->tv_nsec = (x)->tv_nsec;            \
        }                                           \
        else                                        \
        {                                           \
            (z)->tv_sec = (y)->tv_sec;              \
            (z)->tv_nsec = (y)->tv_nsec;            \
        }                                           \
    }                                               \
} while(0)

#define randomstrget()      ((((unsigned long) random()) % 26) + 97)
#define randomuint(max)     (int) (((unsigned long) random()) % max)

#endif // __EXAMPLE_STRING_AVX__
