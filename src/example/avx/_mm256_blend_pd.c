#include <stdio.h>
#include <immintrin.h>

union vector256;

typedef unsigned char   vectoru8x32 __attribute__ ((vector_size(32)));
typedef unsigned short  vectoru16x16 __attribute__ ((vector_size(32)));
typedef unsigned int    vectoru32x8 __attribute__ ((vector_size(32)));
typedef unsigned long   vectoru64x4 __attribute__ ((vector_size(32)));
typedef char            vectori8x32 __attribute__ ((vector_size(32)));
typedef short           vectori16x16 __attribute__ ((vector_size(32)));
typedef int             vectori32x8 __attribute__ ((vector_size(32)));
typedef long            vectori64x4 __attribute__ ((vector_size(32)));
typedef union vector256 vector256;

union vector256
{
    __m256i      i256;
    __m256d      d256;
    __m256       f256;
    vectoru8x32  u8;
    vectoru16x16 u16;
    vectoru32x8  u32;
    vectoru64x4  u64;
    vectori8x32  i8;
    vectori16x16 i16;
    vectori32x8  i32;
    vectori64x4  i64;
};

int main(int argc, char ** argv)
{
    vector256 x = { .u64 = { 0xFFFFFFFFFFFFFFFFUL, 0x0000000000000000UL, 0xFFFFFFFFFFFFFFFFUL, 0x0000000000000000UL } };
    vector256 y = { .u64 = { 0x0000000000000000UL, 0xFFFFFFFFFFFFFFFFUL, 0x0000000000000000UL, 0xFFFFFFFFFFFFFFFFUL } };

    vector256 z = { .d256 = _mm256_blend_pd(x.d256, y.d256, 0x0A) };    // 1010

    printf("convert => { ");
    for(int i = 0; i < 4; i++)
    {
        printf("0x%016lx%s", z.u64[i], i + 1 == 4 ? " }" : ", ");
    }
    printf("\n");

    z.d256 = _mm256_blend_pd(x.d256, y.d256, 0x05); // 0101

    printf("convert => { ");
    for(int i = 0; i < 4; i++)
    {
        printf("0x%016lx%s", z.u64[i], i + 1 == 4 ? " }" : ", ");
    }
    printf("\n");

    return 0;
}