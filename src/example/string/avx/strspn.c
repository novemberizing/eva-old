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

extern unsigned long __attribute__ ((noinline)) xstringspn(const char * __s, const char * __reject) __THROW __attribute_pure__ __nonnull ((1, 2));

typedef char xvectori8x256 __attribute__ ((vector_size(256)));

// typedef double         xvectorf64x4  __attribute__ ((vector_size(32)));

/**
 */
extern unsigned long __attribute__ ((noinline)) xstringspn(const char * __s, const char * __reject)
{
    // xvector256 table[8] = { 0, };
    char table[256] = { 0, };

    for(const char * reject = __reject; *reject; reject++)
    {
        table[*reject] = 1;
    }

    xvectori8x256 reject = { 0, };      // 

    int length = 0;
    
    for(int i = 0; i < 256; i++)
    {
        if(table[i])
        {
            reject[length++] = i;
        }
    }
    // length == 0
    int n = length / 16 + (length % 16 > 0 ? 1 : 0);    // 16 1

    const __m256i * source = (const __m256i *) __s;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    xvector256 value = { .i256 = _mm256_lddqu_si256(source) };

    int mask = 0;

    union {
        int i32[2];
        long i64;
    } z = { 0, };

    xvector128 test[2];

    char c = 0;
    while(!(mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(value.i256, zero))))
    {
        int nonexist = 1;
        test[0].i128 = (__m128i)(xvectori64x2) { 0, };
        test[1].i128 = (__m128i)(xvectori64x2) { 0, };
        for(int i = 0 ; i < n; i++)
        {
            test[0].i128 |= _mm_cmpistrm(_mm_lddqu_si128((__m128i *) &reject[i * 16]), value.i128[0], _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY);
            test[1].i128 |= _mm_cmpistrm(_mm_lddqu_si128((__m128i *) &reject[i * 16]), value.i128[1], _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY);
        }

        if(test[0].i32[0] != 0x0000FFFF || test[1].i32[0] != 0x0000FFFF)
        {
            break;
        }

        value.i256 = _mm256_lddqu_si256(++source);
    }
//    printf("%p %p\n", __s, source);

    int nonexist = 0;
    for(int i = 0; i < 32; i++)
    {
        nonexist = 1;
        for(int j = 0; j < length; j++)
        {
            if(value.i8[i] == reject[j])
            {
                nonexist = 0;
                break;
            }
        }
        if(nonexist)
        {
            return ((char *) source) - __s + i;
        }
    }

    // for(int i = 0; i < 32; i++)
    // {
    //     if(value.i8[i] == c)
    //     {
    //         return ((char *) source) - __s + i;
    //     }
    // }

    return 0;
}

const char * re = "abcdefghijklmnopqrstuvwxyz";

int validate(int index, unsigned long n)
{
    unsigned long k = strspn(experimentalstr[index], re);
//    printf("%ld %ld\n", k, n);
    return n == k;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("strspn    ", unsigned long n = strspn(experimentalstr[index], re), printf("%ld\r", n), validate(index, n));
    experiment("xstringspn", unsigned long n = xstringspn(experimentalstr[index], re), printf("%ld\r", n), validate(index, n));
    
    return 0;
}