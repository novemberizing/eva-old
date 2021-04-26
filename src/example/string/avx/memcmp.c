#include "avx.h"

extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n) __THROW __attribute_pure__ __nonnull ((1, 2));

extern int __attribute__ ((noinline)) xmemorycmp(const void * __x, const void * __y, unsigned long __n)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;
    const __m256i * until = (const __m256i *) (((const char *) __y) + __n - 32);

    if(source <= until)
    {
        while(source <= until && _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), _mm256_load_si256(destination))))
        {
            ++source;
            ++destination;
        }
        --source;
        --destination;
    }
    
 
    register const char * c = (const char *) (source);
    register const char * d = (const char *) (destination);
    int i = 0;
    while(c < (char *)(__y) + __n && *(c++) == *(d++)){
        // printf("%d\n", *c - *d);
        i++;
        //printf("%d\n", *d);
    }
    // printf("count => %d %d %d %c %c\n", i, *(c-1), *(d-1), *(c-1), *(d-1));

    return *(d-1) - *(c-1);
}

int validate(int index, int n)
{
    // printf("%d\n")
    return memcmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256) == n;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    experiment("memcmp    ", int n = memcmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256), printf("%d\r", n), validate(index, n));
    experiment("xmemorycmp", int n = xmemorycmp(experimentalstr[index], expermentalcmpstr[index], 65536 + 256), printf("%d\r", n), validate(index, n));

    printf("%d\n", memcmp("hello\n", "world\n", 6));
    printf("%d\n", xmemorycmp("hello\n", "world\n", 6));

    return 0;
}
