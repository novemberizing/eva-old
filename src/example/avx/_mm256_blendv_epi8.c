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
    vector256 x    = { .u8  = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  } };
    vector256 y    = { .u8  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  } };
    vector256 mask = { .u8  = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  } };

    vector256 z    = { .i256 = _mm256_blendv_epi8(x.i256, y.i256, mask.i256) };

    for(int i = 0; i < 32; i++)
    {
        printf("0x%02x ", z.u8[i]);
    }
    printf("\n");

    mask.u8 = (vectoru8x32) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80  };


    z.i256 = _mm256_blendv_epi8(x.i256, y.i256, mask.i256);

    for(int i = 0; i < 32; i++)
    {
        printf("0x%02x ", z.u8[i]);
    }
    printf("\n");

    return 0;
}
