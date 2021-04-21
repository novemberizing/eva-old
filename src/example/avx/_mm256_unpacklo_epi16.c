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

int main(int argc, char ** argv)
{
    vector256 x = { .u16 = { 0xFF00, 0xEE00, 0xDD00, 0xCC00, 0xBB00, 0xAA00, 0x9900, 0x8800, 0x0077, 0x0066, 0x0055, 0x0044, 0x0033, 0x0022, 0x0011, 0x00FF } };
    vector256 y = { .u16 = { 0x0000, 0x1100, 0x2200, 0x3300, 0x4400, 0x5500, 0x6600, 0x7700, 0x8800, 0x0099, 0x00AA, 0x00BB, 0x00CC, 0x00DD, 0x00EE, 0x00FF } };

    vector256 z = { .i256 = _mm256_unpacklo_epi16(x.i256, y.i256) };

    for(int i = 0; i < 4; i++)
    {
        printf("%016lx\n", z.u64[i]);
    }


    return 0;
}