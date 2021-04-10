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

union xvector256;
union xvector512;

typedef unsigned long xvector64x4 __attribute__ ((vector_size(32)));
typedef unsigned char xvector8x32 __attribute__ ((vector_size(32)));
typedef union xvector256 xvector256;

typedef unsigned long xvector64x8 __attribute__ ((vector_size(64)));
typedef unsigned char xvector8x64 __attribute__ ((vector_size(64)));
typedef union xvector512 xvector512;

union xvector256
{
    __m256i     i256;
    __m256d     d256;
    xvector64x4 u64;
    xvector8x32 u8;
};

union xvector512
{
    __m512i     i512;
    xvector64x8 u64;
    xvector8x64 u8;
};

typedef union xvector256 xvector256;

#define xcheckzero(x)    ((x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL)



unsigned long xstringlen(const char * s)
{
    const __m256i * source = (const __m256i *) s;
    xvector256 zero;
    xvector256 low;
    xvector256 high;
    xvector256 value;
    
    int i = 0;

    zero.u64 = (xvector64x4) { 0, 0, 0, 0 };
    low.u64 = (xvector64x4) { 0x0101010101010101UL, 0x0101010101010101UL, 0x0101010101010101UL, 0x0101010101010101UL };
    high.u64 = (xvector64x4) { 0x8080808080808080UL, 0x8080808080808080UL, 0x8080808080808080UL, 0x8080808080808080UL };

    while(!(zero.u64[0] + zero.u64[1] + zero.u64[2] + zero.u64[3]))
    {
        value.i256 = _mm256_loadu_si256(source++);
        zero.i256 = _mm256_sub_epi64(value.i256, low.i256);
        zero.d256 = _mm256_andnot_pd(value.d256, zero.d256);        
        zero.d256 = _mm256_and_pd(zero.d256, high.d256);
        i = i + 32;
    }
    for(int j = 0; j < 4; j++)
    {
        if(zero.u64[j])
        {
            for(int k = 0; k < 8; k++)
            {
                if(!value.u8[j * 8 + k])
                {
                    return i - 32 + j * 8 + k;
                }
            }
        }
    }

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

        unsigned long n = xstringlen(experimentalstr[index]);

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
    experiment_strlen("strlen     => ");

    return 0;
}
