/**
 * https://pubs.opengroup.org/onlinepubs/009696899/basedefs/string.h.html
 * 
 * gcc -Wall -Wextra -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations  -fsanitize=undefined -mavx strlen.c
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
#include <string.h>

static const int experimentmax = 65536;
static const int experimentalstrcnt = 1024;

static char experimentalstr[1024][65536 + 128];
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

void init(void)
{
    for(int i = 0; i < experimentalstrcnt; i++)
    {
        int n = randomuint(64);
        reallen[i] = 65536 + n;
        for(unsigned long j = 0; j < reallen[i]; j++)
        {
            experimentalstr[i][j] = ((((unsigned long) random()) % 26) + 97);
        }
        experimentalstr[i][reallen[i]] = 0;
    }
}

typedef int v8si __attribute__ ((vector_size(32)));
typedef unsigned long v4u __attribute__ ((vector_size(32)));
typedef char x8c __attribute__ ((vector_size(32)));

union xvector256
{
    __m256i i256;
    v4u     u64;
    x8c     c8;
};

typedef union xvector256 xvector256;

#define xcheckzero(x)    ((x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL)

unsigned long xstringlen(const char * s)
{
    const __m256i * data = (const __m256i *) s;

    do
    {
        xvector256 v = { .i256 = _mm256_loadu_si256(data) };

        v.u64  = xcheckzero(v.u64);
        if(v.u64[0] || v.u64[1] || v.u64[2] || v.u64[3])
        {
            register char * c = &(v.c8[0]);
            while(!*c){ ++c; }
            return ((const char *) data) - s + (c - &(v.c8[0]));
        }
    } while(++data);
    
    return 0;
}

void experiment_strlen(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);


        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        if(n != reallen[index])
        {
            printf("assertion\n");
            exit(-1);
        }
        printf("%ld-%ld.%09ld\r", n, diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void experiment_xstringlen(const char * title)
{
    struct timespec start = { 0, 0};
    struct timespec end = { 0, 0};
    struct timespec diff = { 0, 0};
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);

        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        if(n != reallen[index])
        {
            printf("assertion\n");
            exit(-1);
        }
        printf("%ld-%ld.%09ld\r", n, diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

int main(int argc, char ** argv)
{
    (void)(argc);
    (void)(argv);
    init();

    experiment_xstringlen("xstringlen => ");
    experiment_xstringlen("strlen     => ");

    return 0;
}
