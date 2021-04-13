#include "avx.h"

extern int __attribute__ ((noinline)) xstringcmp(const char * __x, const char * __y) __THROW __attribute_pure__ __nonnull ((1, 2));

extern int __attribute__ ((noinline)) xstringcmp(const char * __x, const char * __y)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;

    while(_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), _mm256_load_si256(destination))))
    {
        ++source;
        ++destination;
    }
    --source;
    --destination;
    
 
    register const char * c = (const char *) (source);
    register const char * d = (const char *) (destination);

    while(*(c++) == *(d++)){}

    return *(d-1) - *(c-1);
}

static int validate(int index, int n)
{
    int result = strcmp(experimentalstr[index], expermentalcmpstr[index]);
    return result == n;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("xstringcmp", int n = xstringcmp(experimentalstr[index], expermentalcmpstr[index]), printf("%d\r", n), validate(index, n));
    experiment("strcmp", int n = strcmp(experimentalstr[index], expermentalcmpstr[index]), printf("%d\r", n), validate(index, n));

    printf("hello world\n");
    return 0;
}
