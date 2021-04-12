

#include "avx.h"

// void *__restrict __dest, const void *__restrict __src,
// 		      int __c, size_t __n

extern void * __attribute__ ((noinline)) xmemorycopy_until(void *__restrict __dest, const void *__restrict __src, int __c, size_t __n) __THROW __attribute_pure__ __nonnull ((1));

extern void * xmemorycopy_until(void *__restrict __dest, const void *__restrict __src, int __c, size_t __n)
{
    const __m256i * source = (const __m256i *) __src;
    
    return __dest;
}

static int validate(int index, void * p)
{
    return 1;
}



int main(int argc, char ** argv)
{
    printf("hello world\n");
    experiment("memccpy", void * p = memccpy(buffer, experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));
    experiment("xmemorycopy_until", void * p = xmemorycopy_until(buffer, experimentalstr[index], 0, 65536 + 256), printf("%p\r", p), validate(index, p));
    return 0;
}
