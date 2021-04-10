/**
 * 
 * $ gcc -Wall -Wextra -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations  -fsanitize=undefined -mavx memcpy.c
 * 
 * $ gcc -O3 -mavx2 memcpy.c
 */
#include "avx.h"

static void * xmemorycopy(void * __restrict __destination, const void * __restrict __source, unsigned long n)
{
    register __m256i *       destination256 = (__m256i *) __destination;
    register const __m256i * source256      = (const __m256i *) __source;
    for(register unsigned long i = 32; i <= n; i = i + 32)
    {
        _mm256_store_si256(destination256++, _mm256_loadu_si256(source256++));
    }
    n = n % 32;
    unsigned long * destination64 = (unsigned long *) destination256;
    unsigned long * source64 = (unsigned long *) source256;
    for(register unsigned long i = 8; i <= n; i = i + 8)
    {
        *((unsigned long *) destination64++) = *((unsigned long *) source64++);
    }
    n = n % 8;
    unsigned char * destination8 = (unsigned char *) destination64;
    unsigned char * source8      = (unsigned char *) source64;
    for(unsigned long i = 0; i < n; i++)
    {
        *((unsigned char *) destination8++) = *((unsigned char *) source8++);
    }

    return __destination;
}

static int validate(int index)
{
    const char * s = experimentalstr[index];
    unsigned long len = reallen[index];
    return (memcmp(buffer, s, len) == 0 && buffer[len] == '@');
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("memcpy", void * p = memcpy(buffer, experimentalstr[index], reallen[index]), printf("%p\r", p), validate(index));
    experiment("xmemorycopy", void * p = xmemorycopy(buffer, experimentalstr[index], reallen[index]), printf("%p\r", p), validate(index));

    return 0;
}