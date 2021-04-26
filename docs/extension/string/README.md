Custom string function example using AVX(Advanced Vector Extension)
===================================================================

> In order to easily implement the protocol in EVA<sup>EVENT LIB</sup>, it is necessary to implement special functions other than the standardy c library. So, I need to implement and practice the string function.

In general, GLIBC outperforms the performance of basic string functions by 400 ~ 2,000 nanoseconds. Also, the performance of the library provided by default is a little more superior. It's a natual result, but some of the results show slightly better results, so I organize them like below. Obviously, the library of GLIBC is evoloving, so if you use the latest version you will get better results. I think that is the power of open source.

It was implemented based on the POSIX standard `<string.h>` document, and the strtok, strtok_r, and strxfrm functions were not implemented. Of cource, Custom string functions can be also bugs and dangerous code (just practice code). Therefore, do not trust it, and use it as a reference if you need to customize the string function. The result of the performance check after testing 65536 times based on a charaeter string of 65536 or 32768 size is as follows, and it is marked in bold on the side with excellent performance.

> https://pubs.opengroup.org/onlinepubs/9699919799/

```sh
$ gcc -mavx2 -O3
```

| Posix Func  | Posix       | Custom Func           |  Custom     | Example Code Link |
| ----------- | ----------- | --------------------- | ----------- | ----------------- |
| memccpy     | 0.000009281 | __xmemorycopy_until__ | 0.000007570 | [code](../../../src/example/string/avx/memccpy.c) |
| __memchr__  | 0.000006226 | xmemorychr            | 0.000006802 | [code](../../../src/example/string/avx/memchr.c) |
| __memcpy__  | 0.000007258 | xmemorycopy           | 0.000007434 | [code](../../../src/example/string/avx/memcpy.c) |
| __memset__  | 0.000001789 | xmemoryset            | 0.000001864 | [code](../../../src/example/string/avx/memset.c) |
| strchr      | 0.000001791 | __xstringchr__        | 0.000001654 | [code](../../../src/example/string/avx/strchr.c) |
| strcpy      | 0.000008659 | __xstringcpy__        | 0.000007739 | [code](../../../src/example/string/avx/strcpy.c) |
| __strdup__  | 0.000009685 | xstringdup            | 0.000011583 | [code](../../../src/example/string/avx/strdup.c) |
| strncat     | 0.000116398 | __xstringncat__       | 0.000009399 | [code](../../../src/example/string/avx/strncat.c) |
| __strncpy__ | 0.000003675 | xstringncpy           | 0.000004135 | [code](../../../src/example/string/avx/strncpy.c) |
| __strrchr__ | 0.000003644 | xstringrchr           | 0.000003987 | [code](../../../src/example/string/avx/strrchr.c) |
| __strstr__  | 0.000008553 | xstringstr            | 0.000011412 | [code](../../../src/example/string/avx/strstr.c) |
| __memcmp__  | 0.000005270 | xmemorycmp            | 0.000005396 | [code](../../../src/example/string/avx/memcmp.c) |
| __memmove__ | 0.000001448 | xmemorymove           | 0.000001928 | [code](../../../src/example/string/avx/memmove.c) |
| strcat      | 0.000113902 | __xstringcat__        | 0.000009198 | [code](../../../src/example/string/avx/strcat.c) |
| __strcmp__  | 0.000005135 | xstringcmp            | 0.000005167 | [code](../../../src/example/string/avx/strcmp.c) |
| strcspn     | 0.000021064 | __xstringcspn__       | 0.000006265 | [code](../../../src/example/string/avx/strcspn.c) |
| __strlen__  | 0.000006645 | xstringlen            | 0.000006844 | [code](../../../src/example/string/avx/strlen.c) |
| __strncmp__ | 0.000004943 | xstringncmp           | 0.000005058 | [code](../../../src/example/string/avx/strncmp.c) |
| strpbrk     | 0.000022519 | __xstringpbrk__       | 0.000006217 | [code](../../../src/example/string/avx/strpbrk.c) |
| strspn      | 0.000021209 | __xstringspn__        | 0.000009482 | [code](../../../src/example/string/avx/strspn.c) |
