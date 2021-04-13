#include "avx.h"

extern char * __attribute__ ((noinline)) xstringcpy(char *__restrict __d, const char *__restrict __s) __THROW __nonnull ((1, 2));

extern char * __attribute__ ((noinline)) xstringcpy (char *__restrict __d, const char *__restrict __s)
{
    const __m256i * source = (const __m256i *) __s;

    __m256i * destination256 = (__m256i *) __d;

    const __m256i value = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };
    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), value)))
    {
        _mm256_store_si256(destination256++, _mm256_load_si256(source++));
    }

    register const char * s = (const char *) source;
    register char * d = (char *) destination256;

    while(*s != 0){ *(d++) = *(s++); }

    *d = *s;

    return (void *) (d + 1);
}

int validate(int index, char * s)
{
    strcpy(buffer, experimentalstr[index]);
    return memcmp(buffer, original, 65536 + 256) == 0;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");

    experiment("xstringcpy", char * s = xstringcpy(original, experimentalstr[index]), printf("%p\r", s), validate(index, s));
    experiment("strcpy", char * s = strcpy(original, experimentalstr[index]), printf("%p\r", s), validate(index, s));

    return 0;
}