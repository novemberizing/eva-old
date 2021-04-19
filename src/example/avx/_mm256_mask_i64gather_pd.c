#include <stdio.h>
#include <immintrin.h>

union vector256;
union vector128;

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

static double values[] = { 0.0f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.1f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f };

int main(int argc, char ** argv)
{
    vector256 source = { .f64 = { 3.3f, 2.2f, 1.1f, 0.0f } };
    vector256 index = { .u64 = { 2, 4, 6, 8 } };
    vector256 mask = { .u64 = { -1, 0, -1, 0 } };
    vector256 z = { .d256 = _mm256_mask_i64gather_pd(source.d256, values, index.i256, mask.i256, 4) };

    for(int i = 0; i < 4; i++)
    {
        printf("%lf\n", z.f64[i]);
    }

    return 0;
}
