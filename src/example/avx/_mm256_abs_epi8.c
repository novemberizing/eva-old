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
    printf("hello _mm256_abs_epi16\n");
    vector256 s = { .i8 = { -15, -14, -13, -12, -11, -10,  -9,  -8,
                             -7,  -6,  -5,  -4,  -3,  -2,  -1,   0,
                              1,   2,   3,   4,   5,   6,   7,   8,
                              9,  10,  11,  12,  13,  14,  15,  16 } };
    printf("original => { ");
    for(int i = 0; i < 32; i++)
    {
        printf("%d%s", s.i8[i], i + 1 == 32 ? " }" : ", ");
    }
    printf("\n");
    vector256 d = { .i256 = _mm256_abs_epi8(s.i256) };
    printf("convert => { ");
    for(int i = 0; i < 32; i++)
    {
        printf("%d%s", d.i8[i], i + 1 == 32 ? " }" : ", ");
    }
    printf("\n");
    return 0;
}