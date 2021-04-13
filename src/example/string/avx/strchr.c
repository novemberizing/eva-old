#include "avx.h"

extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c) __THROW;


extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c)
{
    const __m256i * source = (const __m256i *) __s;
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i zero = (__m256i) (xvectoru64x4) { v, v, v, v };

    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), zero))){ source++; }
    char * c = (char *) source;
    while(*c != __c){ c++; }
    return c;

}

static int validate(int index, char * s)
{
    char * d = strchr(original, '@');
    return d == s;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    experiment("strchr", char * s = strchr(original, '@'), printf("%p\r", s), validate(index, s));
    experiment("xstringchr", char * s = xstringchr(original, '@'), printf("%p\r", s), validate(index, s));
    printf("hello world\n");
    return 0;
}