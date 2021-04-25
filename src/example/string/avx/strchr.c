#include "avx.h"

extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c) __THROW;


/**
 * 
 * 이 함수는 0 을 체크하지 않으니 뭔가 이상하다. 조금 더 확인해봐야겠다.
 */

extern char * __attribute__ ((noinline)) xstringchr(const char * __s, int __c)
{
    const __m256i * source = (const __m256i *) __s;
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i value = (__m256i) (xvectoru64x4) { v, v, v, v };
    const __m256i zero  = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    __m256i temp = _mm256_lddqu_si256(source);
    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(temp, value)))
    {
        source++;
    }
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