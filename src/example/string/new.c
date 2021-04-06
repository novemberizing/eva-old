#include <stdio.h>

int main(int argc, char ** argv)
{
    return 0;
}

// /**
//  * COMPILE -O3
//  */
// #include <x/std.h>
// #include <x/time.h>

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <x/string.h>

// static const int stringlen = 65536;
// static const int examplestrmax = 1024;
// static const int experimentalcount = 65536;

// static char examplestr[1024][65536 + 16];

// #include <stdio.h>
// // typedef int v4si __attribute__ ((vector_size (16)));

// typedef int v4si __attribute__ ((vector_size (16)));


// // size_t sse41_strlen(const char* s) {

// //     size_t result = 0;

// //     const __m128i zeros = _mm_setzero_si128();
// //     __m128i* mem = reinterpret_cast<__m128i*>(const_cast<char*>(s));

// //     for (/**/; /**/; mem++, result += 16) {

// //         const __m128i data = _mm_loadu_si128(mem);
// //         const __m128i cmp  = _mm_cmpeq_epi8(data, zeros);

// //         if (!_mm_testc_si128(zeros, cmp)) {

// //             const auto mask = _mm_movemask_epi8(cmp);

// //             return result + bits::get_first_bit_set(mask);
// //         }
// //     }

// //     assert(false);
// //     return 0;
// // }


// // size_t sse42_strlen(const char* s) {

// //     size_t result = 0;

// //     __m128i* mem = reinterpret_cast<__m128i*>(const_cast<char*>(s));
// //     const __m128i zeros = _mm_setzero_si128();

// //     for (/**/; /**/; mem++, result += 16) {

// //         const __m128i data = _mm_loadu_si128(mem);

// //         const uint8_t mode =
// //             _SIDD_UBYTE_OPS |
// //             _SIDD_CMP_EQUAL_EACH |
// //             _SIDD_LEAST_SIGNIFICANT;

// //         // Note: pcmpstri return mask/index and set ALU flags. Intrinsics
// //         //       functions can return just single value (mask, particular
// //         //       flag), so multiple intrinsics functions have to be called.
// //         //
// //         //       The good news: GCC and MSVC merges multiple _mm_cmpXstrX
// //         //       invocations with the same arguments to the single pcmpstri
// //         //       instruction.
// //         //
// //         if (_mm_cmpistrc(data, zeros, mode)) {
// //             const auto idx = _mm_cmpistri(data, zeros, mode);

// //             return result + idx;
// //         }
// //     }
// // }

// static void examplestrinit(void)
// {
//     for(xint32 i = 0; i < examplestrmax; i++)
//     {
//         for(xint32 j = 0; j < stringlen; j++)
//         {
//             examplestr[i][j] = xrandomunsigned64(26) + 97;
//         }
//         examplestr[i][65536] = 0;
//     }
// }

// static xuint64 xstringlen_word_align(const char * s)
// {
//     for(register unsigned long * o = (unsigned long *) s;;o++)
//     {
//         for(register char * c = (char *) o; c < (char *) (o + 1); c++)
//         {
//             if(*c == 0)
//             {
//                 return c - s;
//             }
//         }
//     }

//     return 0;
// }


// #define haszero(v)  (((v) - 0x0101010101010101UL) & ~(v) & 0x8080808080808080UL)

// extern xuint64 xstringlen_optimize_long(const char * s)
// {
//     register unsigned long * o = (unsigned long *) s;

//     while(++o)
//     {
//         register unsigned long v = *o;
//         if(haszero(v))
//         {
//             register char * c = (char *) o;
//             while(*c != 0){ ++c; }
//             return c - s;
//         }
//     }

//     return 0;
// }
// #define hasNulByte(x) ((x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL)
// #define SW (sizeof (unsigned long int) / sizeof (char))


// extern xuint64 xstrlen (const char *s) {
// const char *p;
// unsigned long int d;

//     p = s - 1;
//     do {
//         p++;
//         if ((((unsigned long int) p) & (SW - 1)) == 0) {
//             do {
//                 d  = *((unsigned long int *) p);
//                 p += SW;
//             } while (!hasNulByte (d));
//             p -= SW;
//         }
//     } while (*p != 0);
//     return p - s;
// }


// extern xuint64 xstringlen_optimize_128(const char * str)
// {
//   const char *char_ptr;
//   const unsigned long int *longword_ptr;
//   unsigned long int longword, himagic, lomagic;

//   /* Handle the first few characters by reading one character at a time.
//      Do this until CHAR_PTR is aligned on a longword boundary.  */
//   for (char_ptr = str; ((unsigned long int) char_ptr
// 			& (sizeof (longword) - 1)) != 0;
//        ++char_ptr)
//     if (*char_ptr == '\0')
//       return char_ptr - str;

//   /* All these elucidatory comments refer to 4-byte longwords,
//      but the theory applies equally well to 8-byte longwords.  */

//   longword_ptr = (unsigned long int *) char_ptr;

//   /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
//      the "holes."  Note that there is a hole just to the left of
//      each byte, with an extra at the end:
//      bits:  01111110 11111110 11111110 11111111
//      bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD
//      The 1-bits make sure that carries propagate to the next 0-bit.
//      The 0-bits provide holes for carries to fall into.  */
//   himagic = 0x80808080L;
//   lomagic = 0x01010101L;
//   if (sizeof (longword) > 4)
//     {
//       /* 64-bit version of the magic.  */
//       /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
//       himagic = ((himagic << 16) << 16) | himagic;
//       lomagic = ((lomagic << 16) << 16) | lomagic;
//     }
//   if (sizeof (longword) > 8)
//     abort ();

//   /* Instead of the traditional loop which tests each character,
//      we will test a longword at a time.  The tricky part is testing
//      if *any of the four* bytes in the longword in question are zero.  */
//   for (;;)
//     {
//       longword = *longword_ptr++;

//       if (((longword - lomagic) & ~longword & himagic) != 0)
// 	{
// 	  /* Which of the bytes was the zero?  If none of them were, it was
// 	     a misfire; continue the search.  */

// 	  const char *cp = (const char *) (longword_ptr - 1);

// 	  if (cp[0] == 0)
// 	    return cp - str;
// 	  if (cp[1] == 0)
// 	    return cp - str + 1;
// 	  if (cp[2] == 0)
// 	    return cp - str + 2;
// 	  if (cp[3] == 0)
// 	    return cp - str + 3;
// 	  if (sizeof (longword) > 4)
// 	    {
// 	      if (cp[4] == 0)
// 		return cp - str + 4;
// 	      if (cp[5] == 0)
// 		return cp - str + 5;
// 	      if (cp[6] == 0)
// 		return cp - str + 6;
// 	      if (cp[7] == 0)
// 		return cp - str + 7;
// 	    }
// 	}
//     }
// }

// extern xuint64 xstringlen_optimize_int(const char * s)
// {
//     for(register unsigned int * o = (unsigned int *) s;;o++)
//     {
//         register unsigned int v = *o;
//         register unsigned int n = 0x7F7F7F7Fu;
//         if(~((((v & n) + n) | v) | n))
//         {
//             register char * c = (char *) o;
//             // while(*c != 0){ ++c; }
//             return c - s;
//         }
//     }

//     return 0;
// }

// extern xuint64 xstringlen_byte(const char * s)
// {
//     register const char * c = s;
//     while(*c){ ++c; }
//     return c - s;
// }

// #include <immintrin.h>
// #include <emmintrin.h>


// typedef unsigned char u8x16 __attribute__ ((vector_size (16)));
// typedef unsigned int  u32x4 __attribute__ ((vector_size (4)));

// typedef union {
//         __m128i mm;
//         u8x16   u8;
//         u32x4   u64[4];
// } v128;

// xuint64 xstringlen_simd(const char * s)
// {

//     // size_t result = 0;


//     //     //     const __m128i cmp  = _mm_cmpeq_epi8(data, zeros);

//     //     // if (!_mm_testc_si128(zeros, cmp)) {

//     //     //     const auto mask = _mm_movemask_epi8(cmp);

//     //     //     return result + bits::get_first_bit_set(mask);
//     //     // }

//     // const register __m128i * mem = (const __m128i *) s;

//     // __m128i zero = _mm_setzero_si128();

//     // const __uint8_t mode =
//     //             _SIDD_UBYTE_OPS |
//     //             _SIDD_CMP_EQUAL_EACH |
//     //             _SIDD_LEAST_SIGNIFICANT;

//     // for(;;++mem, result += 16)
//     // {
//     //     __m128i value = _mm_loadu_si128(mem);

//     //     if (_mm_cmpistrc(value, zero, mode)) {
//     //         int idx = _mm_cmpistri(value, zero, mode);

//     //         return result + idx;
//     //     }
//     // }

//     return 0;

//     // const __m128i zeros = _mm_setzero_si128();
//     // const __m128i * mem = (const __m128i *) s;
//     // const __m128i data = _mm_loadu_si128(mem);



//     // // 1. __m128i * mem = (__m128i *)

//     // // 2. const __m128i * mem = reinterpret_cast<__m128i*>(const_cast<char*>(s));

//     // for (/**/; /**/; mem++, result += 16) {

//     //     const __m128i data = _mm_loadu_si128(mem);
//     //     const __m128i cmp  = _mm_cmpeq_epi8(data, zeros);

//     //     if (!_mm_testc_si128(zeros, cmp)) {

//     //         const auto mask = _mm_movemask_epi8(cmp);

//     //         return result + bits::get_first_bit_set(mask);
//     //     }
//     // }

//     // assert(false);
// }

// //     __m128i * mem = (typedef double __m128d_u __attribute__ ((__vector_size__ (16), __may_alias__, __aligned__ (1)));
// //  *) s;
// //    __m128i * mem =
//     // while(++mem)
//     // {

//     //     // v128 data;
//     //     // data.mm = _mm_loadu_si128(mem);
        
//     //     // printf("u32 => %08x\n", data.u32[0]);

//     //     // break;
//     // }

//     // __m128i* mem = reinterpret_cast<__m128i*>(const_cast<char*>(s));

//     // for (/**/; /**/; mem++, result += 16) {

//     //     const __m128i data = _mm_loadu_si128(mem);
//     //     const __m128i cmp  = _mm_cmpeq_epi8(data, zeros);

//     //     if (!_mm_testc_si128(zeros, cmp)) {

//     //         const auto mask = _mm_movemask_epi8(cmp);

//     //         return result + bits::get_first_bit_set(mask);
//     //     }
//     // }

//     // assert(false);
//     // return 0;
// //     return 0;
// // }

// static void experiment(const char * name, xuint64 (*f)(const char * s), ...);

// static void experiment(const char * name, xuint64 (*f)(const char * s), ...)
// {
//     xtime start = xtimevoid();
//     xtime end = xtimevoid();
//     xtime diff = xtimevoid();
//     xtime max = xtimevoid();
//     xtime min = xtimevoid();
//     xtime avg = xtimevoid();
//     xtime sum = xtimevoid();
//     xuint64 n = 0;
    
//     /** STRLEN */
//     start = xtimevoid();
//     end = xtimevoid();
//     diff = xtimevoid();
//     max = xtimevoid();
//     min = xtimeinit(0x7FFFFFFFFFFFFFFFlu, 0x7FFFFFFFFFFFFFFFlu);
//     avg = xtimevoid();
//     sum = xtimevoid();
//     for(xint32 i = 0; i < experimentalcount; i++)
//     {
//         char * s2 = examplestr[xrandomunsigned64(examplestrmax)];
//         n = xstrlen(s2);
//         // printf("2==== %ld\r", n);
// //        examplestrinit();
//         start = xtimeget();
//         n = f(s2);
//         end = xtimeget();
//         diff = xtimediff(xaddressof(end), xaddressof(start));
//         if(xtimecmp(xaddressof(max), xaddressof(diff)) < 0){ max = diff; }
//         if(xtimecmp(xaddressof(min), xaddressof(diff)) > 0){ min = diff; }
//         // max = xtimecomp()
//         printf("%s %04d %lu %lu.%09lu\r", name, i, n + 1, diff.second, diff.nanosecond);
//         sum.second = sum.second + diff.second;
//         sum.nanosecond = sum.nanosecond + diff.nanosecond;
//     }
//     printf("\r\n");
//     avg = xtimeavg(xaddressof(sum), experimentalcount);
//     printf("%s MAX %d %lu.%09lu\n", name, stringlen, max.second, max.nanosecond);
//     printf("%s MIN %d %lu.%09lu\n", name, stringlen, min.second, min.nanosecond);
//     printf("%s AVG %d %lu.%09lu\n", name, stringlen, avg.second, avg.nanosecond);

// }

// int main(int argc, char ** argv)
// {
//     examplestrinit();
//     xuint64 (*f)(const char * s) = strlen;
// {
//     const char * name = "strlen";
//     xtime start = xtimevoid();
//     xtime end = xtimevoid();
//     xtime diff = xtimevoid();
//     xtime max = xtimevoid();
//     xtime min = xtimevoid();
//     xtime avg = xtimevoid();
//     xtime sum = xtimevoid();
//     xuint64 n = 0;
    
//     /** STRLEN */
//     start = xtimevoid();
//     end = xtimevoid();
//     diff = xtimevoid();
//     max = xtimevoid();
//     min = xtimeinit(0x7FFFFFFFFFFFFFFFlu, 0x7FFFFFFFFFFFFFFFlu);
//     avg = xtimevoid();
//     sum = xtimevoid();
//     for(xint32 i = 0; i < experimentalcount; i++)
//     {
//         char * s2 = examplestr[xrandomunsigned64(examplestrmax)];
//         n = xstrlen(s2);
//         // printf("2==== %ld\r", n);
// //        examplestrinit();
//         start = xtimeget();
//         n = f(s2);
//         end = xtimeget();
//         diff = xtimediff(xaddressof(end), xaddressof(start));
//         if(xtimecmp(xaddressof(max), xaddressof(diff)) < 0){ max = diff; }
//         if(xtimecmp(xaddressof(min), xaddressof(diff)) > 0){ min = diff; }
//         // max = xtimecomp()
//         printf("%s %04d %lu %lu.%09lu\r", name, i, n + 1, diff.second, diff.nanosecond);
//         sum.second = sum.second + diff.second;
//         sum.nanosecond = sum.nanosecond + diff.nanosecond;
//     }
//     printf("\r\n");
//     avg = xtimeavg(xaddressof(sum), experimentalcount);
//     printf("%s MAX %d %lu.%09lu\n", name, stringlen, max.second, max.nanosecond);
//     printf("%s MIN %d %lu.%09lu\n", name, stringlen, min.second, min.nanosecond);
//     printf("%s AVG %d %lu.%09lu\n", name, stringlen, avg.second, avg.nanosecond);

// }

//     // xstringlen_simd("hello world");
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_simd);
    
//     // experiment("STRLEN(OPTIMIZATION-LONG)", strlen);
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_simd);
//     experiment("STRLEN(OPTIMIZATION-LONG)", strlen);
//     experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
//     return 0;




//     // v4si a, b, c;

//     // c = a + b;


//     // examplestrinit();

//     // // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
//     // // experiment("STRLEN(OPTIMIZATION-128)", xstringlen_optimize_128);
//     // // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);


//     // // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);

//     // // experiment("STRLEN", strlen);

//     // // experiment("STRLEN", strlen);
//     // experiment("STRLEN", strlen);
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
//     // experiment("STRLEN", strlen);
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
//     // experiment("STRLEN", strlen);
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
//     // experiment("STRLEN", strlen);
//     // experiment("STRLEN(OPTIMIZATION-LONG)", xstringlen_optimize_long);
    
//     // // printf("\n\n\n\n");


//     // // experiment("STRLEN", strlen);
//     // // experiment("STRLEN(XSTRLEN)", xstrlen);
//     // // experiment("STRLEN(XSTRLEN)", xstrlen2);

    
    
//     // // examplestrinit();

//     // // experiment("XSTRINGLEN[WORD]", xstringlen_word_align);
//     // // experiment("STRLEN", strlen);
//     // // experiment("XSTRINGLEN[BYTE]", xstringlen_byte);
    
//     // // // /** XSTRINGLEN */
//     // // // name = "XSTRINGLEN-WORD";
//     // // // for(xint32 i = 0; i < 1024; i++)
//     // // // {
//     // // //     xtime start = xtimeget();
//     // // //     xuint64 n = xstringlen_word_align(examplestr[xrandomunsigned64(64)]);
//     // // //     xtime end = xtimeget();
//     // // //     xtime diff = xtimediff(xaddressof(end), xaddressof(start));
//     // // //     printf("%s %04d %lu %lu.%09lu\n", name, i, n, diff.second, diff.nanosecond);
//     // // // }
//     // // // printf("%s MAX\n", name);
//     // // // printf("%s MIN\n", name);
//     // // // printf("%s AVG\n", name);
//     // // // /** XSTRINGLEN */
//     // // // name = "XSTRINGLEN-WORD";
//     // // // for(xint32 i = 0; i < 1024; i++)
//     // // // {
//     // // //     xtime start = xtimeget();
//     // // //     xuint64 n = xstringlen_byte(examplestr[xrandomunsigned64(64)]);
//     // // //     xtime end = xtimeget();
//     // // //     xtime diff = xtimediff(xaddressof(end), xaddressof(start));
//     // // //     printf("%s %04d %lu %lu.%09lu\n", name, i, n, diff.second, diff.nanosecond);
//     // // // }
//     // // // printf("%s MAX\n", name);
//     // // // printf("%s MIN\n", name);
//     // // // printf("%s AVG\n", name);
//     // return 0;
// }

