#include "avx.h"

extern unsigned long __attribute__ ((noinline)) xstringcspn(const char * __s, const char * __reject) __THROW __attribute_pure__ __nonnull ((1, 2));

typedef char xvectori8x256 __attribute__ ((vector_size(256)));

// typedef double         xvectorf64x4  __attribute__ ((vector_size(32)));

/**
 */
extern unsigned long __attribute__ ((noinline)) xstringcspn(const char * __s, const char * __reject)
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


    char c = 0;
    while(!(mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(value.i256, zero))))
    {
        for(int i = 0 ; i < n; i++)
        {
            if((z.i32[0] = _mm_cmpistri(value.i128[0], _mm_lddqu_si128((__m128i *) &reject[i * 16]), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY)) < 16)
            {
                c = reject[i * 16 + z.i32[0]];
                break;
            }
            
            if((z.i32[1] = _mm_cmpistri(value.i128[1], _mm_lddqu_si128((__m128i *) &reject[i * 16]), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY)) < 16)
            {
                c = reject[i * 16 + z.i32[1]];
                break;
            }
        }
        if(c)
        {
            printf("%c\n", c);
            break;
        }

        value.i256 = _mm256_lddqu_si256(++source);
    }

    for(int i = 0; i < 32; i++)
    {
        if(value.i8[i] == c)
        {
            return ((char *) source) - __s + i;
        }
    }

    return 0;
}

const char * re = "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+";

int validate(int index, unsigned long n)
{
    unsigned long k = strcspn(experimentalstr[index], re);
    return n == k;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("strcspn    ", unsigned long n = strcspn(experimentalstr[index], "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+"), printf("%ld\r", n), validate(index, n));
    experiment("xstringcspn", unsigned long n = xstringcspn(experimentalstr[index], re), printf("%ld\r", n), validate(index, n));
    
    return 0;
}