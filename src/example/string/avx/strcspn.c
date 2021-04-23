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

    const __m256i * source = (const __m256i *) __s;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    xvector256 value = { .i256 = _mm256_lddqu_si256(source) };

    int mask = 0;

    union {
        int  i32[2];
        long i64;
    } z = { 0, };
    

    while(!z.i64 || !(mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(value.i256, zero))))
    {
        printf("= 2 =\n");

        if((z.i32[0] = _mm_cmpistri(value.i128[0], _mm_lddqu_si128((__m128i *) &reject[0]), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY)))
        {
            z.i32[1] = 0;
            break;
        }
        
        if((z.i32[1] = _mm_cmpistri(value.i128[1], _mm_lddqu_si128((__m128i *) &reject[0]), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY)))
        {
            break;
        }

        // int z = _mm_cmpistri(_mm_lddqu_si128((__m128i *) s), _mm_lddqu_si128((__m128i *) reject), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY);
        value.i256 = _mm256_lddqu_si256(++source);
        

        
        printf("z => %d, %d\n", z.i32[0], z.i32[1]);
    }

    printf("mask => %08x\n", mask);
    printf("%p, %p\n", __s, source);

    

    // 0 까지 읽어 나간다.
    // for(int i = 0; i < length; i++)
    // {
    // }
    // for(int i = 0; i < 8; i++)
    // {
    //     for(int j = 0; j < 32; j++)
    //     {
    //         printf("%c", table[i].u8[j] ? i * 32 + j : ' ');
    //     }
    // }

    for(const char * s = __s; *s; s++)
    {
        if(table[*s])
        {
            return __s - s;
        }
    }

    // 127 shift


    printf("\n");

// __m256i table[8] = {
// };
//   /* Use multiple small memsets to enable inlining on most targets.  */
//   unsigned char table[256];
//   unsigned char *p = memset (table, 0, 64);
//   memset (p + 64, 0, 64);
//   memset (p + 128, 0, 64);
//   memset (p + 192, 0, 64);
//   unsigned char *s = (unsigned char*) __reject;
//   unsigned char tmp;
//   do
//     p[tmp = *s++] = 1;
//   while (tmp);
//   s = (unsigned char*) str;
//   if (p[s[0]]) return 0;
//   if (p[s[1]]) return 1;
//   if (p[s[2]]) return 2;
//   if (p[s[3]]) return 3;
//   s = (unsigned char *) PTR_ALIGN_DOWN (s, 4);
//   unsigned int c0, c1, c2, c3;
//   do
//     {
//       s += 4;
//       c0 = p[s[0]];
//       c1 = p[s[1]];
//       c2 = p[s[2]];
//       c3 = p[s[3]];
//     }
//   while ((c0 | c1 | c2 | c3) == 0);
//   size_t count = s - (unsigned char *) str;
//   return (c0 | c1) != 0 ? count - c0 + 1 : count - c2 + 3;

    return 0;
}

int validate(int index, unsigned long n)
{
    // printf("%ld \n", n);
    return 1;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world novemberizing novemberizing novemberizing\n");

    // experiment("strcspn    ", unsigned long n = strcspn(experimentalstr[index], "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+"), printf("%ld\r", n), validate(index, n));
    // experiment("xstringcspn", unsigned long n = xstringcspn(experimentalstr[index], "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+"), printf("%ld\r", n), validate(index, n));

//    size_t n = xstringcspn("hellk world\n", "dddfsdafsdakjh");  // 
//    printf("%ld\n", n);

    const char * s = "hello world novemberizing novemberizing novemberizing\n";
    printf("%ld\n", strlen(s));
    const char reject[16] = "1234e56";

    // xvector128 z = { .i128 = _mm_cmpistrm(_mm_lddqu_si128((__m128i *) s), _mm_lddqu_si128((__m128i *) reject), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY) };

    // for(int i = 0; i < 4; i++)
    // {
    //     printf("%08x\n", z.u32[i]);
    // }

    int n = xstringcspn(s, reject);
    printf("%d\n", n);

    // int z = _mm_cmpistri(_mm_lddqu_si128((__m128i *) s), _mm_lddqu_si128((__m128i *) reject), _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY);
    // printf("%d\n", z);
    
    return 0;
}