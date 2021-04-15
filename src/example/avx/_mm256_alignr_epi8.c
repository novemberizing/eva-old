#include <stdio.h>
#include <immintrin.h>

union vector256;

typedef unsigned char   vectoru8x32  __attribute__ ((vector_size(32)));
typedef unsigned short  vectoru16x16 __attribute__ ((vector_size(32)));
typedef unsigned int    vectoru32x8  __attribute__ ((vector_size(32)));
typedef unsigned long   vectoru64x4  __attribute__ ((vector_size(32)));
typedef char            vectori8x32  __attribute__ ((vector_size(32)));
typedef short           vectori16x16 __attribute__ ((vector_size(32)));
typedef int             vectori32x8  __attribute__ ((vector_size(32)));
typedef long            vectori64x4  __attribute__ ((vector_size(32)));
typedef float           vectorf32x8  __attribute__ ((vector_size(32)));
typedef double          vectorf64x4  __attribute__ ((vector_size(32)));

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
    vector256 x = { .u64 = { 0x45F2F1E145F2C1E1LU, 0x35F2F1E145F2D1E1LU, 0x25F2F1E145F2E1E1LU, 0x15F2F1E145F2F1E1LU } };
    vector256 y = { .u64 = { 0xF1F1F245E1F1F245LU, 0xE1F1E245E1F1F245LU, 0xD1F1D245E1F1F245LU, 0xC1F1C245E1F1F245LU } };

    vector256 z = { .i256 = _mm256_alignr_epi8(x.i256, y.i256, 6 ) };

    for(int i = 0; i < 4; i++)
    {
        printf("%016lx\n", z.u64[i]);
    }
    return 0;
}
