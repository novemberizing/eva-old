#include "avx.h"

void * __attribute__ ((noinline)) xmemoryset(void *__s, int __c, unsigned long __n) __THROW __nonnull ((1));

void * __attribute__ ((noinline)) xmemoryset(void *__s, int __c, unsigned long __n)
{
    unsigned long v = (unsigned char) __c;
    v |= (v << 8);
    v |= (v << 16);
    v |= (v << 32);

    const __m256i value = (__m256i) (xvectoru64x4) { v, v, v, v };
    __m256i * until256 = (__m256i *)(((unsigned char *) __s) + (__n / 32) * 32);
    __m256i * destination256 = (__m256i *) __s;
    int i = 0;
    while(destination256 != until256)
    {
        i++;
        _mm256_store_si256(destination256++, value);
    }
    char * destination8 = (char *) destination256;
    char * until8 = (((char *) __s) + __n);

    while(destination8 != until8)
    {
        *(destination8++) = __c;
    }

    return __s;
}

static int validate(int index, void * p)
{
    memcpy(buffer, experimentalstr[index], 65536 + 256);
    memset(buffer, '%', 65536 - index);
    return memcmp(buffer, original, 65536 + 256) == 0;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");
    experiment("xmemoryset", void * p = xmemoryset(original, '%', 65536 - index), printf("%p\r", p), validate(index, p));
    experiment("memset", void * p = memset(original, '%', 65536 - index), printf("%p\r", p), validate(index, p));
    
    return 0;
}
