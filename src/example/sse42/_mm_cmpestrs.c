#include <stdio.h>
#include <immintrin.h>

union vector128;

typedef unsigned char   vectoru8x16 __attribute__ ((vector_size(16)));
typedef unsigned short  vectoru16x8 __attribute__ ((vector_size(16)));
typedef unsigned int    vectoru32x4 __attribute__ ((vector_size(16)));
typedef unsigned long   vectoru64x2 __attribute__ ((vector_size(16)));
typedef char            vectori8x16 __attribute__ ((vector_size(16)));
typedef short           vectori16x8 __attribute__ ((vector_size(16)));
typedef int             vectori32x4 __attribute__ ((vector_size(16)));
typedef long            vectori64x2 __attribute__ ((vector_size(16)));
typedef float           vectorf32x4 __attribute__ ((vector_size(16)));
typedef double          vectorf64x2 __attribute__ ((vector_size(16)));
typedef union vector128 vector128;

union vector128
{
    __m128i     i128;
    __m128d     d128;
    __m128      f128;
    vectoru8x16 u8;
    vectoru16x8 u16;
    vectoru32x4 u32;
    vectoru64x2 u64;
    vectori8x16 i8;
    vectori16x8 i16;
    vectori32x4 i32;
    vectori64x2 i64;
    vectorf32x4 f32;
    vectorf64x2 f64;
};

#include <math.h>

int main(int argc, char ** argv)
{
    const char * s = "hello\000 novemberizing!";
    const char * reject = "h12e12345678901234567890";

    vector128 x = { .i128 = _mm_lddqu_si128((__m128i *) s) };
    vector128 y = { .i128 = _mm_lddqu_si128((__m128i *) reject) };

    int z = 0;
    
    z = _mm_cmpestrs(x.i128, 16, y.i128, 16, _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ANY);
    printf("%08x\n", z);

    z = _mm_cmpestrs(x.i128, 16, y.i128, 16, _SIDD_UBYTE_OPS | _SIDD_CMP_RANGES);
    printf("%08x\n", z);

    z = _mm_cmpestrs(x.i128, 16, y.i128, 16, _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH);
    printf("%08x\n", z);

    z = _mm_cmpestrs(x.i128, 16, y.i128, 16, _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ORDERED);
    printf("%08x\n", z);

    return 0;
}