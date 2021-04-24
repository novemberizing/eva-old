#include "avx.h"

char * __attribute__ ((noinline)) xstringcat(char * __restrict __d, const char * __restrict __s, unsigned long n) __THROW __nonnull ((1, 2));


char * __attribute__ ((noinline)) xstringcat(char * __restrict __d, const char * __restrict __s, unsigned long n)
{
    __m256i * destination = (__m256i *) __d;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(destination), zero))){ destination++; }

    char * destination8 = (char *) destination;
    while(*(destination8)){ destination8++; }
    destination = (__m256i *) destination8;

    const __m256i * source = (const __m256i *) __s;
    __m256i v = _mm256_load_si256(source);
    int c = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, zero));
    if(n >= 32)
    {
        while(!c && ((n = n - 32) >= 0))
        {
            _mm256_storeu_si256(destination++, v);
            v = _mm256_load_si256(++source);
            c = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, zero));
        }
    }

    register const char * s = (const char *) (source);
    register char * d = (char *) (destination);

    if(n > 0)
    {
        while(*s && n--)
        {
            *(d++) = *(s++);
        }
        *d = *s;
    }

    return __d;
}

int validate(int index, char * s)
{
    strcat(buffer, experimentalstr[index]);
    return memcmp(buffer, original, 65536 + 1) == 0;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");
    experiment("strncat", char * s = strncat(original, experimentalstr[index], 65536), printf("%p\r", s), validate(index, s));
    experiment("xstringncat", char * s = xstringcat(original, experimentalstr[index], 65536), printf("%p\r", s), validate(index, s));
    return 0;
}