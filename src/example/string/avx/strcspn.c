#include "avx.h"

extern unsigned long __attribute__ ((noinline)) xstringcspn(const char * __s, const char * __reject) __THROW __attribute_pure__ __nonnull ((1, 2));

/**
 */
extern unsigned long __attribute__ ((noinline)) xstringcspn(const char * __s, const char * __reject)
{
    xvector256 table[8] = { 0, };

    for(const char * reject = __reject; *reject; reject++)
    {
        table[(*reject) / 32].u8[(*reject) % 32] = 1;
    }

    // for(int i = 0; i < 8; i++)
    // {
    //     for(int j = 0; j < 32; j++)
    //     {
    //         printf("%c", table[i].u8[j] ? i * 32 + j : ' ');
    //     }
    // }

    for(const char * s = __s; *s; s++)
    {
        if(table[(*s) / 32].u8[(*s) % 32])
        {
            return 1;
        }
    }

    // 127 shift
    

    printf("\n");

// __m256i table[8] = {
// };
//   /* Use multiple small memsets to enable inlining on most targets.  */
//   unsigned char table[256];
//   unsigned char *p = memset (table, 0, 64);
//   memset (p + 64, 0, 64);
//   memset (p + 128, 0, 64);
//   memset (p + 192, 0, 64);
//   unsigned char *s = (unsigned char*) __reject;
//   unsigned char tmp;
//   do
//     p[tmp = *s++] = 1;
//   while (tmp);
//   s = (unsigned char*) str;
//   if (p[s[0]]) return 0;
//   if (p[s[1]]) return 1;
//   if (p[s[2]]) return 2;
//   if (p[s[3]]) return 3;
//   s = (unsigned char *) PTR_ALIGN_DOWN (s, 4);
//   unsigned int c0, c1, c2, c3;
//   do
//     {
//       s += 4;
//       c0 = p[s[0]];
//       c1 = p[s[1]];
//       c2 = p[s[2]];
//       c3 = p[s[3]];
//     }
//   while ((c0 | c1 | c2 | c3) == 0);
//   size_t count = s - (unsigned char *) str;
//   return (c0 | c1) != 0 ? count - c0 + 1 : count - c2 + 3;

    return 0;
}

int validate(int index, unsigned long n)
{
    return 1;
}

int main(int argc, char ** argv)
{
    init(argc, argv);
    printf("hello world\n");

    experiment("strcspn    ", unsigned long n = strcspn(experimentalstr[index], "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+"), printf("%ld\r", n), validate(index, n));
    experiment("xstringcspn", unsigned long n = xstringcspn(experimentalstr[index], "@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+@#$%^&*()_+"), printf("%ld\r", n), validate(index, n));

    size_t n = xstringcspn("hellk world\n", "dddfsdafsdakjh");  // 
    printf("%ld\n", n);
    
    return 0;
}