

#include "avx.h"

// void *__restrict __dest, const void *__restrict __src,
// 		      int __c, size_t __n

extern void * __attribute__ ((noinline)) xmemorycopy_until(void *__restrict __dest, const void *__restrict __src, int __c, size_t __n) __THROW __attribute_pure__ __nonnull ((1));

extern void * xmemorycopy_until(void *__restrict __d, const void *__restrict __s, int __c, size_t __n)
{
    const __m256i * until = (const __m256i *) (((const char *) __s) + (__n & ~31));
    const __m256i * source = (const __m256i *) __s;

    __m256i * destination256 = (__m256i *) __d;

    const __m256i value = _mm256_set1_epi8(__c);

    while(source <= until && !_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_lddqu_si256(source), value)))
    {
        _mm256_store_si256(destination256++, _mm256_load_si256(source++));
    }

    register const char * s = (const char *) source;
    register char * d = (char *) destination256;

    while(*s != __c){ *(d++) = *(s++); }

    return (void *) (d + 1);
}

static int validate(int index, void * p)
{
    return (((char *) p) - buffer - 1) == reallen[index];
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");
    experiment("memccpy", void * p = memccpy(buffer, experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));
    experiment("xmemorycopy_until", void * p = xmemorycopy_until(buffer, experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));

    printf("%p\n", memccpy(buffer, "hello world\n", ' ', 12));
    printf("%p\n", xmemorycopy_until(buffer, "hello world\n", ' ', 12));
    return 0;
}
