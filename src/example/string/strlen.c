#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

static const int experimentmax = 65536;
static const int experimentalstrcnt = 1024;

static char experimentalstr[1024][65536 + 128];

#define timespec_diff(x, y, out) do {               \
    (out)->tv_sec = (x)->tv_sec - (y)->tv_sec;            \
    (out)->tv_nsec = (x)->tv_nsec - (y)->tv_nsec;         \
    if((out)->tv_nsec < 0) {                          \
        (out)->tv_sec = (out)->tv_sec - 1;              \
        (out)->tv_nsec = 1000000000 + (out)->tv_nsec;   \
    }                                               \
} while(0)

#define randomstrget()      ((((unsigned long) random()) % 26) + 97)
#define randomuint(max)     (int) (((unsigned long) random()) % max)

void init(void)
{
    for(int i = 0; i < experimentalstrcnt; i++)
    {
        int n = randomuint(64);
        for(int j = 0; j < 65536 + n; j++)
        {
            experimentalstr[i][j] = ((((unsigned long) random()) % 26) + 97);
        }
        experimentalstr[i][65536 + n] = 0;
    }
}


void __attribute__((optimize("O0"))) experiment_optimize_0(const char * title)
{
    struct timespec * x;
    struct timespec * y;
    struct timespec * out;
    struct timespec start = { 0, 0};
    struct timespec end = { 0, 0};
    struct timespec diff = { 0, 0};
    struct timespec max = { 0, 0};
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);


        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        printf("%ld-%ld.%09ld\r", n, diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void __attribute__((optimize("O1"))) experiment_optimize_1(const char * title)
{
    struct timespec * x;
    struct timespec * y;
    struct timespec * out;
    struct timespec start = { 0, 0};
    struct timespec end = { 0, 0};
    struct timespec diff = { 0, 0};
    struct timespec max = { 0, 0};
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);


        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        printf("%ld-%ld.%09ld\r", n, diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void __attribute__((optimize("O2"))) experiment_optimize_2(const char * title)
{
    struct timespec * x;
    struct timespec * y;
    struct timespec * out;
    struct timespec start = { 0, 0};
    struct timespec end = { 0, 0};
    struct timespec diff = { 0, 0};
    struct timespec max = { 0, 0};
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);


        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
        printf("%ld-%ld.%09ld\r", n, diff.tv_sec, diff.tv_nsec);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
    }

    avg.tv_sec  = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;

    printf("%s %ld.%09ld\n", title, avg.tv_sec, avg.tv_nsec);
}

void __attribute__((optimize("O3"))) experiment_optimize_3(const char * title)
{
    struct timespec * x;
    struct timespec * y;
    struct timespec * out;
    struct timespec start = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec max = { 0, 0 };
    struct timespec min = { 0x7FFFFFFFFFFFFFFFUL, 0x7FFFFFFFFFFFFFFFUL };
    struct timespec avg = { 0, 0};
    for(int i = 0; i < experimentmax; i++)
    {
        int index = randomuint(experimentalstrcnt);
        clock_gettime(CLOCK_REALTIME, &start);


        unsigned long n = strlen(experimentalstr[index]);

        clock_gettime(CLOCK_REALTIME, &end);
        timespec_diff(&end, &start, &diff);
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
    init();

    experiment_optimize_0("no optimize => ");
    experiment_optimize_1("o1 optimize => ");
    experiment_optimize_2("o2 optimize => ");
    experiment_optimize_3("o3 optimize => ");

    return 0;
}
