#include <stdio.h>
#include <immintrin.h>
#include <string.h>

typedef int v8si __attribute__ ((vector_size(32)));
typedef unsigned long v4u __attribute__ ((vector_size(32)));
typedef char x8c __attribute__ ((vector_size(32)));

union xvector256
{
    __m256i i256;
    v4u     u64;
    x8c     c8;
    
};

typedef union xvector256 xvector256;

#define xcheckzero(x)    ((x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL)

unsigned long xstringlen(const char * s)
{
    const __m256i * data = (const __m256i *) s;

    do
    {
        xvector256 v = { .i256 = _mm256_loadu_si256(data) };

        v.u64  = xcheckzero(v.u64);
        if(v.u64[0] || v.u64[1] || v.u64[2] || v.u64[3])
        {
            register char * c = &(v.c8[0]);
            while(!*c){ ++c; }
            return ((const char *) data) - s + (c - &(v.c8[0]));
        }
    } while(++data);
    
    return 0;
}

int main(int argc, char ** argv)
{
    // {
    //     v8si v = { 1, 2, 3, 4, 5, 6, 7, 8 };

    //     printf("sizeof(v4si) => %ld\n", sizeof(v8si));
    //     for(int i = 0; i < 8; i++)
    //     {
    //         printf("v[%d] => %d\n", i, v[i]);
    //     }
    // }

    // {
    //     v4u v = { 1, 2, 3, 4 };
    //     printf("sizeof(v4u) => %ld\n", sizeof(v4u));
    //     for(int i = 0; i < 4; i++)
    //     {
    //         printf("v[%d] => %ld\n", i, v[i]);
    //     }
    // }

    const char * s = "1234567890123456789012345678901234567890\000";
    printf("%02x\n", s[0]);
    
    printf("%ld\n", xstringlen(s));
    printf("%ld\n", strlen(s));
    return 0;
}

