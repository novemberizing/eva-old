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
typedef float           vectorf32x8 __attribute__ ((vector_size(32)));
typedef double          vectorf64x4 __attribute__ ((vector_size(32)));
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
    vectorf32x8  f32;
    vectorf64x4  f64;
};

int main(int argc, char ** argv)
{
    vector256 x = { .f32 = { -7.1f, -6.2f, -5.3f, -4.4f, -3.5f, -2.6f, -1.7f, 0.8f } };
    vector256 y = { .f32 = {  0.8f,  1.7f,  2.6f,  3.5f,  4.4f,  5.3f,  6.2f, 7.1f  } };

    vector256 z = { .f256 = _mm256_add_ps(x.f256, y.f256) };

        printf("convert => { ");
    for(int i = 0; i < 8; i++)
    {
        printf("%f%s", z.f32[i], i + 1 == 8 ? " }" : ", ");
    }
    printf("\n");

    return 0;
}