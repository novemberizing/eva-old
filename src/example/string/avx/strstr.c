/**
 * strstr - find a substring
 * 

```c
#include <string.h>

char * strstr(const char * s1, const char * s2);
```

The strstr() function shall locate the first occurence in the string pointed to by s1 of the
sequence of bytes (excluding the terminate null byte) in the string pointed to by s2.

Return

Upon successful completion, strstr() shall return a pointer to the located string or a null
pointer if the string is not found.

If s2 pointed to a string with zero length, the function shall return s1.

 * 
 */
/**
 * 
strspn - get length of a substring

Synopsis

```c
#include <string.h>

size_t strspn(const char *s1, const char *s2);
```

The strspn() function shall compute the length (in bytes) of the maximum initial segment of the string pointed to by s1
which consists entirely of bytes from the string pointed to by s2.

Return

The strspn() function shall return the length of s1; no return value is reserved to indicate an error.

 */

#include "avx.h"

extern char * __attribute__ ((noinline)) xstringstr(const char *__haystack, const char *__needle) __THROW __attribute_pure__ __nonnull ((1, 2));
extern int __attribute__ ((noinline)) xstringcmp(const char * __x, const char * __y) __THROW __attribute_pure__ __nonnull ((1, 2));
extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c) __THROW;
extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n) __THROW __attribute_pure__ __nonnull ((1, 2));

extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;
    const __m256i * until = (const __m256i *) (((const char *) __y) + __n - 32);
    int count = 0;
    if(source <= until)
    {
        while(source <= until && _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_lddqu_si256(source), _mm256_lddqu_si256(destination))))
        {
            ++source;
            ++destination;
        }
        count++;
        --source;
        --destination;
    }
//    printf("count => %d\n", count);
    
//    unsigned long n = __n - ((char * )(__y) - (char *)(source));
    const char * untilc = (char *)(__y) + __n;
    
    register const char * c = (const char *) (source);
    register const char * d = (const char *) (destination);
    int i = 0;
    while(c < untilc && *(c++) == *(d++))
    {
        i++;
    }

    return *(d-1) - *(c-1);
}

extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c)
{
    const __m256i * source = (const __m256i *) __s;
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i value = (__m256i) (xvectoru64x4) { v, v, v, v };
    const __m256i zero  = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    __m256i temp = _mm256_lddqu_si256(source);
    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(temp, value)))
    {
        source++;
    }
    char * c = (char *) source;
    while(*c != __c){ c++; }

    return c;
}

extern int __attribute__ ((noinline)) xstringcmp(const char * __x, const char * __y)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;

    while(_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), _mm256_load_si256(destination))))
    {
        source++;
        destination++;
    }
    source--;
    destination--;
    register const char * c = (const char *) (source);
    register const char * d = (const char *) (destination);

    while(*(c++) == *(d++)){}

    return *(d-1) - *(c-1);
}

typedef char xvectori8x256 __attribute__ ((vector_size(256)));

extern char * __attribute__ ((noinline)) xstringstr(const char *__haystack, const char *__needle)
{
    const __m256i * source = (const __m256i *) __haystack;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };
    xvector256 value = { .i256 = _mm256_lddqu_si256(source) };
    char c = __needle[0];
    unsigned long length = strlen(__needle);
    if(length == 0)
    {
        return 0;
    }

    // xvector256 last = { .i256 = _mm256_lddqu_si256(((char *) source) + length - 1) };

    unsigned long v = (unsigned char) c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i c256 = (__m256i) (xvectoru64x4) { v, v, v, v };

    unsigned long z = __needle[length - 1];
    z |= (z << 8);
    z |= (z << 16);
    z |= (z << 32);

    const __m256i z256 = (__m256i) (xvectoru64x4) { z, z, z, z };
    int mask = 0;
    
    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(value.i256, zero)))
    {
        if((mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(value.i256, c256))))
        {
            if(_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_lddqu_si256((__m256i *)((char *)(source) + length - 1)), z256)))
            {
                // last block 
                char * s = (char *) source;
                for(int i = 0; i < 32 && mask; i++)
                {
                    if(mask & 0x01)
                    {
                        if(xmemorycmp(__needle, s + i, length) == 0)
                        {
                            return s + i;
                        }
                    }
                    mask = (mask >> 1);
                }
            }
        }
        value.i256 = _mm256_lddqu_si256(++source);
    }

    return 0;
}

const char * re = "abcdefghijklmnopqrstuvwxyz";

const char * hello = "hello novemberizing! hello novemberizing!";

int validate(int index, char * p)
{
    char * k = strstr(experimentalstr[index], hello);
//    unsigned long k = strspn(experimentalstr[index], re);
//     printf("%p %p\n", k, p);
    return p == k;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    

    // printf("%ld\n", strlen("hello novemberizing! hello novemberizing!"));
    experiment("strstr", char * p = strstr(experimentalstr[index], hello), printf("%p\r", p), validate(index, p));
    experiment("xstringstr", char * p = xstringstr(experimentalstr[index], hello), printf("%p\r", p), validate(index, p));
//    experiment("strspn    ", unsigned long n = strspn(experimentalstr[index], re), printf("%ld\r", n), validate(index, n));
//    experiment("xstringspn", unsigned long n = xstringspn(experimentalstr[index], re), printf("%ld\r", n), validate(index, n));
    
    return 0;
}