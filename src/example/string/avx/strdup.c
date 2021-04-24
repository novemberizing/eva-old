#include "avx.h"

char * mem = (void *) 0;


extern char * __attribute__ ((noinline)) strdup (const char *__s) __THROW __attribute_malloc__ __nonnull ((1));



extern char * __attribute__ ((noinline)) xstringdup(const char *__s)
{
    const __m256i * source = (const __m256i *) __s;
    const __m256i zero = (__m256i) (xvectoru64x4) { 0, 0, 0, 0 };
    unsigned long len = 0;
    while(!_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), zero))){ source++; }
    register xvector256 value = { .i256 = _mm256_loadu_si256(source) };

    for(int k = 0; k < 32; k++)
    {
        if(!value.u8[k])
        {
            len = ((const char *)source - __s) + k;
            break;
        }
    }

    char * ret = malloc(len + 1);
    ret[len] = 0;

    register __m256i *       destination256 = (__m256i *) ret;
    register const __m256i * source256      = (const __m256i *) __s;
    for(register unsigned long i = 32; i <= len; i = i + 32)
    {
        _mm256_storeu_si256(destination256++, _mm256_load_si256(source256++));
    }
    len = len % 32;
    unsigned long * destination64 = (unsigned long *) destination256;
    unsigned long * source64 = (unsigned long *) source256;
    for(register unsigned long i = 8; i <= len; i = i + 8)
    {
        *((unsigned long *) destination64++) = *((unsigned long *) source64++);
    }
    len = len % 8;
    unsigned char * destination8 = (unsigned char *) destination64;
    unsigned char * source8      = (unsigned char *) source64;
    for(unsigned long i = 0; i < len; i++)
    {
        *((unsigned char *) destination8++) = *((unsigned char *) source8++);
    }

    return ret;

}

int validate(int index, char * m)
{
    int ret = strcmp(experimentalstr[index], m);

    free(m);

    return ret == 0;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("strdup", mem = strdup(experimentalstr[index]), printf("%p\r", mem), validate(index, mem));
    experiment("xstringdup", mem = xstringdup(experimentalstr[index]), printf("%p\r", mem), validate(index, mem));

    return 0;
}