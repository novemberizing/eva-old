`_mm256_setr_epi32(e7: int, e6: int, e5: int, e4: int, e3: int, e2: int, e1: int, e0: int): __m256i`
===========================================================================

> Set packed 32 bit integers in destination with the supplied values in reverse order.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_setr_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0)
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[31:0] := e7
dst[63:32] := e6
dst[95:64] := e5
dst[127:96] := e4
dst[159:128] := e3
dst[191:160] := e2
dst[223:192] := e1
dst[255:224] := e0
dst[MAX:256] := 0
```

