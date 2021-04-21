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

// ```
// FOR j := 0 to 1
// 	i := j*32
// 	m := j*64
// 	IF mask[i+31]
// 		addr := base_addr + vindex[m+63:m] * ZeroExtend64(scale) * 8
// 		dst[i+31:i] := MEM[addr+31:addr]
// 	ELSE
// 		dst[i+31:i] := src[i+31:i]
// 	FI
// ENDFOR
// mask[MAX:64] := 0
// dst[MAX:64] := 0
// ```
// __m128 _mm_mask_i64gather_ps (__m128 src, float const* base_addr, __m128i vindex, __m128 mask, const int scale);

int main(int argc, char ** argv)
{
    vector128 source = { .i32 = { 1, 2, 3, 4 } };
    vectoru64x2 x = { 0xFFEEDDCCBBAA9988UL, 0x7766554433221100UL };
    vector128 index = { .u64 = { 1, 2 } };
    vector128 mask = { .i64 = { -1, 0, } };

    vector128 z = { .f128 = _mm_mask_i64gather_ps(source.f128, &x[0], index.i128, mask.i128, 1) };

    for(int i = 0; i < 4; i++)
    {
        printf("%08x\n", z.i32[i]);
    }

    return 0;
}