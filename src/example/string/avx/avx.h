#ifndef   __EXAMPLE_AVX__H__
#define   __EXAMPLE_AVX__H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

union xvector128;
union xvector256;
union xvector512;

typedef long           xvectori64x2  __attribute__ ((vector_size(16)));
typedef int            xvectori32x4  __attribute__ ((vector_size(16)));
typedef short          xvectori16x8  __attribute__ ((vector_size(16)));
typedef char           xvectori8x16  __attribute__ ((vector_size(16)));
typedef unsigned long  xvectoru64x2  __attribute__ ((vector_size(16)));
typedef unsigned int   xvectoru32x4  __attribute__ ((vector_size(16)));
typedef unsigned short xvectoru16x8  __attribute__ ((vector_size(16)));
typedef unsigned char  xvectoru8x16  __attribute__ ((vector_size(16)));
typedef float          xvectorf32x4  __attribute__ ((vector_size(16)));
typedef double         xvectorf64x2  __attribute__ ((vector_size(16)));

typedef union xvector128 xvector128;

typedef long           xvectori64x4  __attribute__ ((vector_size(32)));
typedef int            xvectori32x8  __attribute__ ((vector_size(32)));
typedef short          xvectori16x16 __attribute__ ((vector_size(32)));
typedef char           xvectori8x32  __attribute__ ((vector_size(32)));
typedef unsigned long  xvectoru64x4  __attribute__ ((vector_size(32)));
typedef unsigned int   xvectoru32x8  __attribute__ ((vector_size(32)));
typedef unsigned short xvectoru16x16 __attribute__ ((vector_size(32)));
typedef unsigned char  xvectoru8x32  __attribute__ ((vector_size(32)));
typedef float          xvectorf32x8  __attribute__ ((vector_size(32)));
typedef double         xvectorf64x4  __attribute__ ((vector_size(32)));
// typedef __m128i        xvectori128x2 __attribute__ ((vector_size(32)));

typedef union xvector256 xvector256;

union xvector256
{
    __m256i       i256;
    __m256d       d256;
    __m256        f256;
    __m128i       i128[2];
    xvectoru64x4  u64;
    xvectoru32x8  u32;
    xvectoru16x16 u16;
    xvectoru8x32  u8;
    xvectori64x4  i64;
    xvectori32x8  i32;
    xvectori16x16 i16;
    xvectori8x32  i8;
};

union xvector128
{
    __m128i       i128;
    __m128d       d128;
    __m128        f128;
    xvectoru64x2  u64;
    xvectoru32x4  u32;
    xvectoru16x8 u16;
    xvectoru8x16  u8;
    xvectori64x2  i64;
    xvectori32x4  i32;
    xvectori16x8 i16;
    xvectori8x16  i8;
};


static const int experimentmax = 65536;
static const int experimentalstrcnt = 1024;

static char experimentalstr[1024][65536 + 256];
static unsigned long reallen[1024];

static char expermentalcmpstr[1024][65536 + 256];
static unsigned long realcmplen[1024];

static char buffer[65536 + 65536 + 256 + 256];
static char original[65536 + 65536 + 256 + 256];

#define randomuint(max)     (((unsigned long) random()) % max)
#define randomcharget()     (char) (randomuint(26) + 97)

static inline void init(int argc, char ** argv)
{
    (void)(argc);
    (void)(argv);
    srandom(time(0));

    for(int i = 0; i < experimentalstrcnt; i++)
    {
        int n = randomuint(64);
        reallen[i] = 65536 + n;
        realcmplen[i] = 65536/2 + randomuint(64);
        for(unsigned long j = 0; j < reallen[i]; j++)
        {
            expermentalcmpstr[i][j] = experimentalstr[i][j] = randomcharget();
        }
        experimentalstr[i][reallen[i]] = 0;
        expermentalcmpstr[i][realcmplen[i]] = 0;
        for(unsigned long j = reallen[i] + 1; j < 65536 + 256; j++)
        {
            experimentalstr[i][j] = '!';
        }
        for(unsigned long j = realcmplen[i] + 1; j < 65536 + 256; j++)
        {
            expermentalcmpstr[i][j] = '!';
        }
        // (65536/4) * 3
        // hello

        experimentalstr[i][65536/2 + 4092 + randomuint(64)] = '@';
        expermentalcmpstr[i][65536/2 + 4092 + randomuint(64)] = '@';
        experimentalstr[i][65536 + 255] = 0;
        expermentalcmpstr[i][65536 + 255] = 0;
        const char * hello = "hello novemberizing! hello novemberizing!";
        memcpy(&(experimentalstr[i][(65536/4) * 3 + randomuint(64)]), hello, strlen(hello));
        memcpy(&(expermentalcmpstr[i][(65536/4) * 3 + randomuint(64)]), hello, strlen(hello));
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

#define experiment(title, code, result, validate) do {                      \
    struct timespec start = { 0, 0 };                                       \
    struct timespec end   = { 0, 0 };                                       \
    struct timespec diff  = { 0, 0 };                                       \
    struct timespec max   = { 0, 0 };                                       \
    struct timespec min   = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL }; \
    struct timespec avg   = { 0, 0 };                                       \
    for(int i = 0; i < experimentmax; i++) {                                \
        memset(buffer, '@', 65536 + 65536 + 256 + 256);                     \
        memset(original, '@', 65536 + 65536 + 256 + 256);                   \
        int index = (int) randomuint(1024);                                 \
        memcpy(original, experimentalstr[(index + 1) % 1024], 65536 + 256); \
        memcpy(buffer, experimentalstr[(index + 1) % 1024], 65536 + 256);   \
        clock_gettime(CLOCK_REALTIME, &start);                              \
        code;                                                               \
        clock_gettime(CLOCK_REALTIME, &end);                                \
        result;                                                             \
        if(!validate) {                                                     \
            printf("                                   \r");                \
            printf("assertion\n");                                          \
            exit(0);                                                        \
        }                                                                   \
        timespecdiff(&end, &start, &diff);                                  \
        timespecmax(&diff, &max, &max);                                     \
        timespecmin(&diff, &min, &min);                                     \
        avg.tv_sec = avg.tv_sec + diff.tv_sec;                              \
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;                           \
    }                                                                       \
    avg.tv_sec  = avg.tv_sec  / experimentmax;                              \
    avg.tv_nsec = avg.tv_nsec / experimentmax;                              \
    printf("                                   \r");                        \
    printf("%s,%ld.%09ld,%ld.%09ld,%ld.%09ld\n", title,                     \
                                                 min.tv_sec, min.tv_nsec,   \
                                                 max.tv_sec, max.tv_nsec,   \
                                                 avg.tv_sec, avg.tv_nsec);  \
} while(0)

#endif // __EXAMPLE_AVX__H__
