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
    vector256 x = { .i16 = { 0x7FF0, 0x7FF1, 0x7FF2, 0x7FF3, 0x7FF4, 0x7FF5, 0x7FF6, 0x7FF7, 0x7FF8, 0x7FF9, 0x7FFA, 0x7FFB, 0x7FFC, 0x7FFD, 0x7FFE, 0x7FFF } };
    vector256 y = { .i16 = {      0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15 } };

    vector256 z = { .i256 = _mm256_adds_epi16(x.i256, y.i256) };

        printf("convert => { ");
    for(int i = 0; i < 16; i++)
    {
        printf("%d%s", z.i16[i], i + 1 == 16 ? " }" : ", ");
    }
    printf("\n");

    return 0;
}