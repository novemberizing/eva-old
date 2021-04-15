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
    vector256 x = { .f64 = { -4.0f, -3.0f, -2.0f,  -1.0f } };
    vector256 y = { .f64 = {  0.4f,  0.3f,  0.2f,   0.1f } };

    vector256 z = { .d256 = _mm256_addsub_pd(x.d256, y.d256) };

    printf("convert => { ");
    for(int i = 0; i < 4; i++)
    {
        printf("%f%s", z.f64[i], i + 1 == 8 ? " }" : ", ");
    }
    printf("\n");

    return 0;
}