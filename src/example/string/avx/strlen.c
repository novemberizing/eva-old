/**
 * 
 * $ gcc -Wall -Wextra -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations  -fsanitize=undefined -mavx memcpy.c
 * 
 * $ gcc -O3 -mavx2 memcpy.c
 * 
 * // SEG FAULT -- no inline ...
 */
#include "avx.h"

// unsigned long xstringlen(const char * s) __attribute__((nothrow));

extern unsigned long __attribute__ ((noinline)) xstringlen(const char * s) __THROW __attribute_pure__ __nonnull ((1));

extern unsigned long __attribute__ ((noinline)) xstringlen(const char * s)
{
    const __m256i * source = (const __m256i *) s;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), zero))){ source++; }
    register xvector256 value = { .i256 = _mm256_loadu_si256(source) };
    for(int k = 0; k < 32; k++)
    {
        if(!value.u8[k])
        {
            return ((const char *)source - s) + k;
        }
    }

    return 0;
}

static int validate(int index, unsigned long n)
{
    const char * s = experimentalstr[index];
    unsigned long len = reallen[index];
//    printf("n => %ld\n", n);
//    printf("n => %ld\n", len);
    return n == len;
}

void experiment_xstringlen(const char * title) {
    struct timespec start = { 0, 0 };
    struct timespec end   = { 0, 0 };
    struct timespec diff  = { 0, 0 };
    struct timespec max   = { 0, 0 };
    struct timespec min   = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg   = { 0, 0 };
    for(int i = 0; i < experimentmax; i++) {
        memset(buffer, '@', 65536 + 256);
        int index = (int) randomuint(1024);
        const char * s = experimentalstr[index];
        clock_gettime(CLOCK_REALTIME, &start);
        unsigned long n = xstringlen(s);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("%ld\r", n);
        if(!validate(index, n)) {
            printf("                                   \r");
            printf("assertion\n");
            exit(0);
        }
        timespecdiff(&end, &start, &diff);
        timespecmax(&diff, &max, &max);
        timespecmin(&diff, &min, &min);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    avg.tv_sec  = avg.tv_sec  / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;
    printf("                                   \r");
    printf("%s,%ld.%09ld,%ld.%09ld,%ld.%09ld\n", title,
                                                 min.tv_sec, min.tv_nsec,
                                                 max.tv_sec, max.tv_nsec,
                                                 avg.tv_sec, avg.tv_nsec);
}

void experiment_strlen(const char * title) {
    struct timespec start = { 0, 0 };
    struct timespec end   = { 0, 0 };
    struct timespec diff  = { 0, 0 };
    struct timespec max   = { 0, 0 };
    struct timespec min   = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg   = { 0, 0 };
    for(int i = 0; i < experimentmax; i++) {
        memset(buffer, '@', 65536 + 256);
        int index = (int) randomuint(1024);
        clock_gettime(CLOCK_REALTIME, &start);
        unsigned long n = strlen(experimentalstr[index]);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("%ld\r", n);
        if(!validate(index, n)) {
            printf("                                   \r");
            printf("assertion\n");
            exit(0);
        }
        timespecdiff(&end, &start, &diff);
        timespecmax(&diff, &max, &max);
        timespecmin(&diff, &min, &min);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    avg.tv_sec  = avg.tv_sec  / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;
    printf("                                   \r");
    printf("%s,%ld.%09ld,%ld.%09ld,%ld.%09ld\n", title,
                                                 min.tv_sec, min.tv_nsec,
                                                 max.tv_sec, max.tv_nsec,
                                                 avg.tv_sec, avg.tv_nsec);
}


int main(int argc, char ** argv)
{
    init(argc, argv);

    // experiment("function xstringlen", unsigned long n = xstringlen(experimentalstr[index]), printf("%ld\r", n), validate(index, n));
    // experiment("function xstringlen", unsigned long n = strlen(experimentalstr[index]), printf("%ld\r", n), validate(index, n));

    experiment_xstringlen("function xstringlen");
    experiment_strlen    ("function strlen    ");

    printf("%ld\n", strlen("hello world\n"));
    printf("%ld\n", xstringlen("hello world\n"));
    
    return 0;
}
