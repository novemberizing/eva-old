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
    vector256 x    = { .u32 = { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
                                0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000  } };
    vector256 y    = { .u32 = { 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF } };
    vector256 mask = { .u32 = { 0x80000000, 0x80000000, 0x80000000, 0x80000000,
                                0x00000000, 0x00000000, 0x00000000, 0x00000000 } };

    vector256 z    = { .f256 = _mm256_blendv_ps(x.f256, y.f256, mask.f256) };

    for(int i = 0; i < 8; i++)
    {
        printf("0x%08x ", z.u32[i]);
    }
    printf("\n");

    mask.u32 = (vectoru32x8) { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                               0x80000000, 0x80000000, 0x80000000, 0x80000000  };


    z.f256 = _mm256_blendv_ps(x.f256, y.f256, mask.f256);

    for(int i = 0; i < 8; i++)
    {
        printf("0x%08x ", z.u32[i]);
    }
    printf("\n");

    return 0;
}