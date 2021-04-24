#include "avx.h"

extern int __attribute__ ((noinline)) xstringncmp(const char * __x, const char * __y, unsigned long n) __THROW __attribute_pure__ __nonnull ((1, 2));

extern int __attribute__ ((noinline)) xstringncmp(const char * __x, const char * __y, unsigned long n)
{
    const __m256i * source = (const __m256i *) __y;
    const __m256i * destination = (const __m256i *) __x;

    if(n >= 32)
    {
        while(_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_load_si256(source), _mm256_load_si256(destination))) && ((n = n -32) >= 0))
        {
            source++;
            destination++;
        }
        source--;
        destination--;
    }
    
    register const char * c = (const char *) (source);
    register const char * d = (const char *) (destination);

    if(n > 0)
    {
        while(*(c++) == *(d++))
        {
            if(n--)
            {
                return 0;
            }
        }
    }
    

    return *(d-1) - *(c-1);
}

static int validate(int index, int n)
{
    int result = strncmp(experimentalstr[index], expermentalcmpstr[index], 65536 / 2);
//    printf("%d %d\n", result, n);
    return result == n;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("xstringncmp", int n = xstringncmp(experimentalstr[index], expermentalcmpstr[index], 65536 / 2), printf("%d\r", n), validate(index, n));
    experiment("strncmp", int n = strncmp(experimentalstr[index], expermentalcmpstr[index], 65536 / 2), printf("%d\r", n), validate(index, n));

    printf("hello world\n");
    return 0;
}
