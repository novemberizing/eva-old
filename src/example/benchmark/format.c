#include <x/std.h>
#include <x/time.h>

#include <stdio.h>
#include <string.h>

static xuint64 xstringlen(const char * s)
{
    if(s)
    {
        for(register const unsigned long * p = (const unsigned long *) s;; ++p)
        {
            const unsigned long * max = p + 1;
            for(register const char * c = (const char *) p; c < (const char *) max; ++c)
            {
                if(*c == 0)
                {
                    return c - s;
                }
            }
        }
    }
    return 0;
}

static char * xstringformat(char * s, xuint64 * index, xuint64 * capacity, const char * format, ...)
{
    if(s)
    {
        for(register const unsigned long * p = (const unsigned long *) format;; ++p)
        {
            const unsigned long * max = p + 1;
            for(register const char * c = (const char *) p; c < (const char *) max; ++c)
            {
                if(*c == 0)
                {
                    return c - s;
                }
            }
        }
    }
    return 0;

    return s;
}

static char original[32][66000];
static char dest[66000];

int main(int argc, char ** argv)
{
    printf("xstringlen() => %lu\n", xstringlen("hello\n"));
    printf("strlen() => %lu\n", strlen("hello\n"));
    printf("xstringlen() => %lu\n", xstringlen("hello world\n"));
    printf("strlen() => %lu\n", strlen("hello world\n"));

    xrandominit();
    for(int k = 0; k < 32; k++)
    {
        for(int i = 0; i < 65536; i++)
        {
            original[k][i] = xrandomunsigned64(26) + 97;
        }
        original[k][8192] = 0;
    }

    printf("STRLEN\n");
    for(xint32 i = 0; i < 64; i++)
    {
        xtime start = xtimeget();
        xuint64 n = strlen(original[xrandomunsigned64(32)]);
        xtime end = xtimeget();
        xtime diff = xtimediff(xaddressof(end), xaddressof(start));
        printf("%ld.%09ld\t%lu\n", diff.second, diff.nanosecond, n);
    }

    printf("XSTRINGLEN\n");

    for(xint32 i = 0; i < 64; i++)
    {
        xtime start = xtimeget();
        xuint64 n = xstringlen(original[xrandomunsigned64(32)]);
        xtime end = xtimeget();
        xtime diff = xtimediff(xaddressof(end), xaddressof(start));
        printf("%ld.%09ld\t%lu\n", diff.second, diff.nanosecond, n);
    }


    printf("STRLEN\n");
    for(xint32 i = 0; i < 64; i++)
    {
        xtime start = xtimeget();
        xuint64 n = strlen(original[xrandomunsigned64(32)]);
        xtime end = xtimeget();
        xtime diff = xtimediff(xaddressof(end), xaddressof(start));
        printf("%ld.%09ld\t%lu\n", diff.second, diff.nanosecond, n);
    }

    printf("XSTRINGLEN\n");

    for(xint32 i = 0; i < 64; i++)
    {
        xtime start = xtimeget();
        xuint64 n = xstringlen(original[xrandomunsigned64(32)]);
        xtime end = xtimeget();
        xtime diff = xtimediff(xaddressof(end), xaddressof(start));
        printf("%ld.%09ld\t%lu\n", diff.second, diff.nanosecond, n);
    }


    return 0;
}
