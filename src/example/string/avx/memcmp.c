#include "avx.h"

extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n) __THROW __attribute_pure__ __nonnull ((1, 2));

extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;
    const __m256i * until = (const __m256i *) (((const char *) __y) + __n - 32);

    while(source <= until && _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), _mm256_load_si256(destination))))
    {
        ++source;
        ++destination;
    }
 
    register const char * c = (const char *) (source - 1);
    register const char * d = (const char *) (destination - 1);

    while(*(c++) == *(d++)){}

    return *(d-1) - *(c-1);
}

int validate(int index, int n)
{
    return memcmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256) == n;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    experiment("memcmp    ", int n = memcmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256), printf("%d\r", n), validate(index, n));
    experiment("xmemorycmp", int n = xmemorycmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256), printf("%d\r", n), validate(index, n));
    return 0;
}
