#ifndef   __EXAMPLE_AVX__H__
#define   __EXAMPLE_AVX__H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>

union xvector256;
union xvector512;

typedef unsigned long xvectoru64x4 __attribute__ ((vector_size(32)));
typedef unsigned char xvectoru8x32 __attribute__ ((vector_size(32)));
typedef union xvector256 xvector256;

union xvector256
{
    __m256i      i256;
    __m256d      d256;
    xvectoru64x4 u64;
    xvectoru8x32 u8;
};


static const int experimentmax = 65536;
static const int experimentalstrcnt = 1024;

static char experimentalstr[1024][65536 + 256];
static unsigned long reallen[1024];

static char expermentalcmpstr[1024][65536 + 256];
static unsigned long realcmplen[1024];

static char buffer[65536 + 256];

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
        experimentalstr[i][65536 + 255] = 0;
        expermentalcmpstr[i][65536 + 255] = 0;
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
        memset(buffer, 0, 65536 + 256);                                   \
        int index = (int) randomuint(1024);                                 \
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
