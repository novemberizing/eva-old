/**
https://pubs.opengroup.org/onlinepubs/009696899/functions/memcpy.html

memcpy - copy bytes in memory

```
#include <string.h>

void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
```

The functionality described on this reference page is aligned with the ISO C standard.
Any conflict between the requirements described here and the ISO C standard is unintentional.
This volume of IEEE Std 1003.1-2001 defers to the ISO C standard.

The memcpy() function shall copy n bytes from the object pointed to by s2 into the object pointed to by s1. If copying takes place between objects that overlap, the behavior is undefined.

Return

The memcpy() function shall return s1; no return value is reserved to indicate an error.

Error

No errors are defined.

APPLICATION USAGE

The memcpy() function does not check for the overflow of the receiving memory area.

 */



int main(int argc, char ** argv)
{
    return 0;
}
