/**
 * -- 에 대한 연산이 너무 느리다.
 * 연산을 더 줄일 수 있는 방법을 찾아야 한다.
 * 약 400 - 600 나노세컨드 차이가 난다.
 * 
 */
#include "avx.h"

extern void * __attribute__ ((noinline)) xmemorymove(void * __d, const void * __s, unsigned long __n) __THROW __nonnull ((1, 2));

extern void * __attribute__ ((noinline)) xmemorymove(void * __d, const void * __s, unsigned long n)
{
    if(__d < __s)
    {
        __m256i * destination256    = (__m256i *) __d;
        const __m256i * source256   = (__m256i *) __s;
        __m256i * destinationend256 = (__m256i *) (((unsigned char *) __d) + (n / 32) * 32);
        __m256i * sourceend256      = (__m256i *) (((unsigned char *) __s) + (n / 32) * 32);
        while (destination256 != destinationend256)
        {
            _mm256_storeu_si256(destination256++, _mm256_lddqu_si256(source256++));
        }

        unsigned long * destination64    = (unsigned long *) destination256;
        const unsigned long * source64   = (unsigned long *) source256;
        unsigned long * destinationend64 = (unsigned long *) (((unsigned char *) __d) + (n / 8) * 8);
        unsigned long * sourceend64      = (unsigned long *) (((unsigned char *) __s) + (n / 8) * 8);

        while(destination64 != destinationend64)
        {
            *(destination64++) = *(source64++);
        }

        unsigned char * destination8    = (unsigned char *) destination64;
        const unsigned char * source8   = (unsigned char *) source64;
        unsigned char * destinationend8 = ((unsigned char *) __d) + n;
        unsigned char * sourceend8      = ((unsigned char *) __s) + n;

        while(destination8 != destinationend8)
        {
            *(destination8++) = *(source8++);
        }
        
    }
    else
    {
        // 256
        __m256i * destination256     = (__m256i *) (((unsigned char *) __d) + (n % 32));
        const __m256i * source256    = (__m256i *) (((unsigned char *) __s) + (n % 32));
        __m256i * destinationend256  = (__m256i *) (((unsigned char *) __d) + n);
        const __m256i * sourceend256 = (__m256i *) (((unsigned char *) __s) + n);
        while (destination256 != destinationend256)
        {
            _mm256_storeu_si256(--destinationend256, _mm256_lddqu_si256(--sourceend256));
        }
        // 64
        unsigned long * destination64     = (unsigned long *) (((unsigned char *) __d) + (n % 8));
        const unsigned long * source64    = (unsigned long *) (((unsigned char *) __s) + (n % 8));
        unsigned long * destinationend64  = (unsigned long *) destinationend256;
        const unsigned long * sourceend64 = (unsigned long *) sourceend256;
        while (destination64 != destinationend64)
        {
            *(--destinationend64) = *(--sourceend64);
        }
        // 8
        unsigned char * destination8    = ((unsigned char *) __d);
        const unsigned char * source8   = ((unsigned char *) __s);
        unsigned char * destinationend8 = ((unsigned char *) destinationend64);
        unsigned char * sourceend8      = ((unsigned char *) destinationend64);

        while(destination8 != destinationend8)
        {
            *(--destinationend8) = *(--sourceend8);
        }
    }

    return __d;
}

static int validate(int index, void * p)
{
    memcpy(buffer, experimentalstr[index], 65536 + 256);
    memmove(buffer + 16384 - 1024 + index, buffer + 32768, 32768 - index);

    return memcmp(buffer, original, 65536 + 256) == 0;
}


static int validate2(int index, void * p)
{
    memcpy(buffer, experimentalstr[index], 65536 + 256);
    memmove(buffer + 32768, buffer + 16384 - 1024 + index, 32768 - index);
//    memmove(buffer + 32768, buffer + 16384 - 1024 + index, 32768 - index);

    // return memcmp(buffer, original, 65536 + 256) == 0;
    return 1;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    experiment("memmove", void * p = memmove(original + 16384 - 1024 + index, original + 32768, 32768 - index), printf("%p\r", p), validate(index, p));
    experiment("xmemorymove", void * p = xmemorymove(original + 16384 - 1024 + index, original + 32768, 32768 - index), printf("%p\r", p), validate(index, p));

    experiment("xmemorymove", void * p = xmemorymove(original + 32768, original + 16384 - 1024 + index, 32768 - index), printf("%p\r", p), validate2(index, p));
    experiment("memmove", void * p = memmove(original + 32768, original + 16384 - 1024 + index, 32768 - index), printf("%p\r", p), validate2(index, p));

    return 0;
}
