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


// #include "avx.h"

// extern char * __attribute__ ((noinline)) xstringrchr(const char * __s, int __c) __THROW;


// extern char * __attribute__ ((noinline)) xstringrchr(const char * __s, int __c)
// {
//     const __m256i * source = (const __m256i *) __s;
//     unsigned long v = (unsigned char) __c;
//     v |= (v << 8);
//     v |= (v << 16);
//     v |= (v << 32);

//     const __m256i zero = (__m256i) (xvectoru64x4) { v, v, v, v };

//     while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), zero))){ source++; }
//     char * c = (char *) source;
//     while(*c != __c){ c++; }
//     return c;

// }

// static int validate(int index, char * s)
// {
//     char * d = strchr(original, '@');
//     return d == s;
// }

// int main(int argc, char ** argv)
// {
//     init(argc, argv);
//     experiment("strchr", char * s = strrchr(original, '@'), printf("%p\r", s), validate(index, s));
//     experiment("xstringchr", char * s = xstringrchr(original, '@'), printf("%p\r", s), validate(index, s));
//     printf("hello world\n");
//     return 0;
// }