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
    vectorf32x4  f32;
    vectorf64x2  f64;
};

#include <math.h>

int main(int argc, char ** argv)
{
    long double nan64 = NAN;

    vector128 x = { .f32 = { nan64, 0.0f, 1.0f, 2.0f } };
    vector128 y = { .f32 = {  1.0f, 1.0f, 1.0f, 1.0f } };
    vector128 z = { 0, };

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_LT_OQ);

    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf < %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NGE_UQ);

    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf < %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_LE_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf <= %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NGT_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf <= %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_EQ_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf == %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_EQ_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf == %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }


    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NEQ_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf != %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NEQ_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf != %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_GE_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf >= %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NLT_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf >= %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_GT_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf > %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_NLE_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf > %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_ORD_Q);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf > %lf true %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_TRUE_UQ);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf true %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_FALSE_OQ);
    for(int i = 0; i < 4; i++)
    {
        printf("ordered: %lf > %lf false %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    z.f128 = _mm_cmp_ss(x.f128, y.f128, _CMP_UNORD_Q);
    for(int i = 0; i < 4; i++)
    {
        printf("unordered: %lf false %lf = %s %08x\n", x.f32[i], y.f32[i], z.u32[i] ? "true" : "false", z.u32[i]);
    }

    return 0;
}