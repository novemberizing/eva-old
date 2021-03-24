#include <stdio.h>

#include <x/string.h>
#include <x/string/format.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);

    char * s = xnil;
    xuint64 index = 0;
    xuint64 capacity = 0;

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "hello world\n");
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "%s", "hello world\n");
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Characters: %c %c \n", 'a', 65);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Decimals: %d %ld\n", 1977, 650000L);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Preceding with blanks: %10d \n", 1977);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Preceding with zeros: %010d \n", 1977);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "Width trick: %*d \n", 5, 10);
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    index = 0;
    capacity = 0;
    s = xsprintf(s, xaddressof(index), xaddressof(capacity), "%s \n", "A string");
    printf("[%lu/%lu] %s", index, capacity, s);
    s = xobjectrem(s);

    return 0;
}
