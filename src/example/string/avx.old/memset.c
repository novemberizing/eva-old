// $ gcc -O3 -mavx memset.c
#include "avx.h"

char buffer[65536 + 128];

static void * xmemoryset(void * destination, int c, unsigned long n)
{
    printf("                                               \r");
    unsigned long v = c;
    v |= v <<  8;
    v |= v << 16;
    v |= v << 32;
    __m256i * dest = (__m256i *) destination;
    __m256i v256 = _mm256_set_epi64x(v, v, v, v);
    for(unsigned long i = 32; i <= n; i = i + 32)
    {
        _mm256_store_si256(dest++, v256);
    }

    n = n % 32;

    unsigned long * destu64 = (unsigned long *) dest;
    for(unsigned long i = 0; i < (n / 8); i++)
    {
        *((unsigned long *) destu64++) = v;
    }

    n = n % 8;
    unsigned char * o = (unsigned char *) destu64;
    while(n--)
    {
        *(o++) = c;
    }
    return destination;
}

void experiment_xmemoryset(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec avg = { 0, 0 };
    struct timespec max = { 0, 0 };
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };

    for(int i = 0; i < experimentmax; i++)
    {
        memset(buffer, 0, 65536 + 128);
        int index = randomuint(1024);
        const char * s = experimentalstr[index];
        unsigned long len = reallen[index];
        char c = randomstrget();

        clock_gettime(CLOCK_REALTIME, &start);

        void * p = xmemoryset(buffer, c, len);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        timespecmax(&max, &diff, &max);
        timespecmin(&min, &diff, &min);
        printf("%p %ld\r", p, len);
        
        for(int j = 0; j < reallen[index]; j++)
        {
            if(c != buffer[j])
            {
                printf("                                          \r");
                printf("assertion: %d < %ld\n", j, len);
                exit(1);
            }
        }
        avg.tv_sec  = avg.tv_sec  + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    avg.tv_sec  = avg.tv_sec  / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;
    printf("                                                           \r");
    printf("%s %ld.%09ld %ld.%09ld %ld.%09ld\n", title,
                                                 min.tv_sec, min.tv_nsec,
                                                 max.tv_sec, max.tv_nsec,
                                                 avg.tv_sec, avg.tv_nsec);
}


void experiment_memset(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec avg = { 0, 0 };
    struct timespec max = { 0, 0 };
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };

    for(int i = 0; i < experimentmax; i++)
    {
        memset(buffer, 0, 65536 + 128);
        int index = randomuint(1024);
        const char * s = experimentalstr[index];
        unsigned long len = reallen[index];
        char c = randomstrget();

        clock_gettime(CLOCK_REALTIME, &start);

        void * p = memset(buffer, c, len);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        timespecmax(&max, &diff, &max);
        timespecmin(&min, &diff, &min);
        printf("%p %ld\r", p, len);
        for(int j = 0; j < reallen[index]; j++)
        {
            if(c != buffer[j])
            {
                printf("assertion\n");
                exit(1);
            }
        }
        avg.tv_sec  = avg.tv_sec  + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }
    avg.tv_sec  = avg.tv_sec  / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;
    printf("                                                           \r");
    printf("%s %ld.%09ld %ld.%09ld %ld.%09ld\n", title,
                                                 min.tv_sec, min.tv_nsec,
                                                 max.tv_sec, max.tv_nsec,
                                                 avg.tv_sec, avg.tv_nsec);
}

int main(int argc, char ** argv)
{
    init();

    experiment_memset    ("memset     => ");
    experiment_xmemoryset("xmemoryset => ");
    return 0;
}