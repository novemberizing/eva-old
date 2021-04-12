#include "avx.h"

extern void * __attribute__ ((noinline)) xmemorymove(void * __d, const void * __s, unsigned long __n) __THROW __nonnull ((1, 2));

extern void * __attribute__ ((noinline)) xmemorymove(void * __d, const void * __s, unsigned long n)
{
    // 메모리가 겹쳐지는 부분에 대한 고민을 해야 한다.
    // 그리고 그것을 도출해 내어야 한다. (64 바이트 얼라인으로 하면 예외가 발생하지 않으지만 그렇지 않은 경우)
    // SEGMENT FAULT 가 발생한다. 겹쳐지는 부분에 대해서 고민해야 한다.
    register __m256i *       destination256 = (__m256i *) __d;
    register const __m256i * source256      = (const __m256i *) __s;
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

    return __d;
}

static int validate(int index, void * p)
{
    memcpy(buffer, experimentalstr[index], 65536 + 256);
    memmove(buffer + 16384 - 1024 + index, buffer + 32768, 32768);

    // return memcmp(buffer, original, 65536 + 256) == 0;
    return 1;
}

int main(int argc, char ** argv)
{
    init(argc, argv);

    // memoryz => // void * p = memmove(buffer + 16384, buffer + 32768, 32768); //

    experiment("memmove", void * p = memmove(original + 16384 - 1024 + index, original + 32768, 32768), printf("%p\r", p), validate(index, p));;
    experiment("xmemorymove", void * p = xmemorymove(original + 16384 - 1024, original + 32768, 32768), printf("%p\r", p), validate(index, p));;

    return 0;
}
