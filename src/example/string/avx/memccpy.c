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



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
        (z)->tv_sec = (y)->tv_nsec;                 \
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
        (z)->tv_sec = (y)->tv_nsec;                 \
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

static const int experimentmax = 65536;
static const int experimentstrcnt = 1024;

static char experimentstr[1024][65536 + 128];
static unsigned long experimentstrlen[1024];

static void init(void)
{
    for(int i = 0; i < experimentstrcnt; ++i)
    {
        unsigned long j = 0;
        experimentstrlen[i] = 65536 + randomuint(64);
        for(; j < experimentstrlen[i]; ++j)
        {
            experimentstr[i][j] = randomstrget();
        }
        experimentstr[i][j] = 0;
        for(j = j + 1; j < 65536 + 64; ++j)
        {
            experimentstr[i][j] = randomstrget();
        }
    }
}

void experiment_memccpy(const char * title)
{
    struct timespec start = { 0, 0 };
    struct timespec end = { 0, 0 };
    struct timespec avg = { 0, 0 };
    struct timespec diff = { 0, 0 };
    struct timespec max = { 0, 0 };
    struct timespec min = { 0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF };
    char buffer[65536 + 128];
    for(int i = 0; i < experimentmax; i++)
    {
        unsigned long index = randomuint(1024);
        unsigned long n = experimentstrlen[index];
        const char * s = experimentstr[index];

        clock_gettime(CLOCK_REALTIME, &start);
        char * p = memccpy(buffer, s, 0, 65536 + 128);
        clock_gettime(CLOCK_REALTIME, &end);
        if(n != (unsigned long) (p - buffer - 1))
        {
            printf("assertion long result n => %lu, %p, %p, %lu\n", n, p, buffer, p - buffer - 1);
            printf("%lu\n", strlen(s));
            exit(0);
        }
        timespecdiff(&end, &start, &diff);
        timespecmax(&diff, &max, &max);
        timespecmin(&diff, &min, &min);
        avg.tv_sec = avg.tv_sec + diff.tv_sec;
        avg.tv_nsec = avg.tv_nsec + diff.tv_nsec;
        printf("%p => \r", p);
    }
    avg.tv_sec = avg.tv_sec / experimentmax;
    avg.tv_nsec = avg.tv_nsec / experimentmax;
    printf("%s %ld.%09ld %ld.%09ld %ld.%09ld\n", title, min.tv_sec, min.tv_nsec,
                                                        max.tv_sec, max.tv_nsec,
                                                        avg.tv_sec, avg.tv_nsec);
}

static void * xmemorycopy_until(void * __restrict destination, const void * __restrict source, int c, unsigned long n)
{
    printf("implement this\n");
    exit(0);

    return 0;
}

void experiment_xmemorycopy_until(const char * title)
{
    (void)(title);
}

int main(int argc, char ** argv)
{
    (void)(argc);
    (void)(argv);

    init();

    experiment_memccpy("memccpy =>");

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