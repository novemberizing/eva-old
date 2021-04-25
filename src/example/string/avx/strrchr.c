/**
 * 

strrchr - string scanning operation

```c
#include <string.h>

char *strrchr(const char *s, int c);
```

The strrchr() function shall locate the last occurence of c (converted to a char) in the string pointed to by s.
The terminate null byte is considered to be part of the string.

## Return

Upon successful completion, strrchr() shall return a pointer to the byte or a null pointer if c does not occur in the string.

## Examples

Finding the base name of a file

The following example uses strrchr() to get a pointer to the base name of a file.
The strrchr() function searches backwards through the name of the file to find the last '/' character in name.
This pointer (plus one) will point to the base name of the file.

```
#include <string.h>

...
const char *name;
char *basename;
...
basename = strrchr(name, '/') + 1;
...

```
 */

#include "avx.h"

extern char * __attribute__ ((noinline)) xstringrchr(const char * __s, int __c) __THROW;


extern char * __attribute__ ((noinline)) xstringrchr(const char * __s, int __c)
{
    const __m256i * source = (const __m256i *) __s;
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i value = (__m256i) (xvectoru64x4) { v, v, v, v };
    const __m256i zero  = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    __m256i temp = _mm256_lddqu_si256(source);
    const __m256i * found = (void *) 0;

    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(temp, zero)))
    {
        if(_mm256_movemask_epi8(_mm256_cmpeq_epi8(temp, value)))
        {
            found = source;
        }

        temp = _mm256_lddqu_si256(++source);
    }
    char * cfp = (void *) 0;
    if(found)
    {
        char * c = (char * ) found;
        for(int i = 0; i <32; i++)
        {
            if(*c == __c)
            {
                cfp = c;
            }
            c++;
        }
    }
    char * c = (char *) source;
    while(*c)
    {
        // *c != __c && 
        if(*c == __c)
        {
            cfp = c;
        }
        c++;
    }

    return cfp;

}

static int validate(int index, char * s)
{
    char * d = strrchr(original, '@');
//    printf("%p %p\n", s, d);
    return d == s;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    experiment("strcrhr", char * s = strrchr(original, '@'), printf("%p\r", s), validate(index, s));
    experiment("xstringchr", char * s = xstringrchr(original, '@'), printf("%p\r", s), validate(index, s));
    printf("hello world\n");
    return 0;
}