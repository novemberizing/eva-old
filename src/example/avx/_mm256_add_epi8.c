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
    vector256 x = { .i8 = { -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1,  0 } };
    vector256 y = { .i8 = {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 } };

    vector256 z = { .i256 = _mm256_add_epi8(x.i256, y.i256) };

    printf("convert => { ");
    for(int i = 0; i < 32; i++)
    {
        printf("%d%s", z.i8[i], i + 1 == 32 ? " }" : ", ");
    }
    printf("\n");

    return 0;
}