`_mm256_setr_epi64x(e3: __int64, e2: __int64, e1: __int64, e0: __int64): __m256i`
========================================================================

> Set packed 64 bit integers in destination with the supplied values in reverse order.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_setr_epi64x (__int64 e3, __int64 e2, __int64 e1, __int64 e0)
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[63:0] := e3
dst[127:64] := e2
dst[191:128] := e1
dst[255:192] := e0
dst[MAX:256] := 0
```

