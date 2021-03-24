#include <stdio.h>

#include <x/string.h>

int main(int argc, char ** argv)
{
    char * s = xnil;
    xuint64 index = 0;
    xuint64 capacity = 0;
    s = xstringcpy(s, xaddressof(index), xaddressof(capacity), "hello world\n");
    printf("[%ld/%ld] %s", index, capacity, s);

    s = xobjectrem(s);
    // xstring s = xstring_void;
    // xstringcpy(xaddressof(s), "hello");

    // printf("%s\n", s.stream);

    // xstringcat(xaddressof(s), " ");
    // xstringcat(xaddressof(s), "world");

    // printf("%s\n", s.stream);

    // xstringcat(xaddressof(s), " ");
    // xstringcat(xaddressof(s), "eva lib simple string example code.");

    // printf("%s\n", s.stream);

    // xstringclr(xaddressof(s));
    return 0;
}