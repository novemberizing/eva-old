#include <stdio.h>

#include <immintrin.h>

union xdouble256
{
    __m256d d256;
    double  d64[2];
};

typedef union xdouble256 xdouble256;


// #include <immintrin.h>

// typedef unsigned char u8x16 __attribute__ ((vector_size (16)));
// typedef unsigned int  u32x4 __attribute__ ((vector_size (16)));
// typedef union {
//         __m128i mm;
//         u8x16   u8;
//         u32x4   u32;
// } v128;

int main(int argc, char ** argv)
{
    printf("sizeof(__m256d) => %lu\n", sizeof(__m256d));
    printf("sizeof(xdouble256) => %lu\n", sizeof(xdouble256));
    return 0;
}