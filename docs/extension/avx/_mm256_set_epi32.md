`_mm256_set_epi32(e7: int, e6: int, e5: int, e4: int, e3: int, e2: int, e1: int, e0: int): __m256i`
===================================================================================================

> Set packed 32-bit integers in dst with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0);
```

## Operation

```
dst[31:0] := e0
dst[63:32] := e1
dst[95:64] := e2
dst[127:96] := e3
dst[159:128] := e4
dst[191:160] := e5
dst[223:192] := e6
dst[255:224] := e7
dst[MAX:256] := 0
```
