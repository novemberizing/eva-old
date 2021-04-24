#include "avx.h"

extern char * __attribute__ ((noinline)) xstringncpy(char *__restrict __d, const char *__restrict __s, unsigned long n) __THROW __nonnull ((1, 2));

extern char * __attribute__ ((noinline)) xstringncpy (char *__restrict __d, const char *__restrict __s, unsigned long n)
{
    const __m256i * source = (const __m256i *) __s;

    __m256i * destination256 = (__m256i *) __d;

    const __m256i value = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };

    if(n >= 32)
    {
        while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), value)) && n >= 32)
        {
            _mm256_store_si256(destination256++, _mm256_load_si256(source++));
            n = n - 32;
        }
    }

    register const char * s = (const char *) source;
    register char * d = (char *) destination256;

    if(n > 0)
    {
        while(*s != 0 && n--)
        {
            *(d++) = *(s++);
        }
    }

    *d = *s;

    return (void *) (d + 1);
}

int validate(int index, char * s)
{
    strncpy(buffer, experimentalstr[index], 65536/2);
    return strncmp(buffer, original, 65536/2) == 0;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");

    experiment("xstringncpy", char * s = xstringncpy(original, experimentalstr[index], 65536 / 2), printf("%p\r", s), validate(index, s));
    experiment("strncpy", char * s = strncpy(original, experimentalstr[index], 65536 / 2), printf("%p\r", s), validate(index, s));

    return 0;
}