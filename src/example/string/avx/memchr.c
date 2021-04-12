
/**
 * 
 * 
 * gcc -mavx2 -O3 memchr.c
 */


#include "avx.h"

extern void * __attribute__ ((noinline)) xmemorychr(const void * __s, int __c, unsigned long __n) __THROW __attribute_pure__ __nonnull ((1));;

extern void * __attribute__ ((noinline)) xmemorychr(const void * __s, int __c, unsigned long __n)
{
    register const __m256i * source = (const __m256i *) __s;
    const __m256i * until = (const __m256i *) (((const char *) __s) + __n - 32);
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i zero = (__m256i) (xvector64x4) { v, v, v, v };
    while(source <= until && !_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), zero)))
    {
        source++;
    }
    
    register const char * c = (const char *) source;
    while(*(c++) != __c){}

    return (void *) (c - 1);
}


static int validate(int index, void * p)
{
    char * __p = (char *) p;
    char * s = experimentalstr[index];
    // printf("%016lx - %016lx, %ld, %ld\n", __p, s, __p - s, reallen[index]);

    return __p - s == reallen[index];
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    
    experiment("xmemorychr", void * p = xmemorychr(experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));
    experiment("memchr    ", void * p = memchr(experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));

    printf("%p\n", xmemorychr("hello world\n", ' ', 12));
    printf("%p\n", memchr("hello world\n", ' ', 12));

    return 0;
}
