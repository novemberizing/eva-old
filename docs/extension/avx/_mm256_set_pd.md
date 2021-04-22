`_mm256_set_pd(e3: double, e2: double, e1: double, e0: double): __m256d`
========================================================================

> Set packed double precision (64 bit) floating point elements in destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_set_pd (double e3, double e2, double e1, double e0);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[63:0] := e0
dst[127:64] := e1
dst[191:128] := e2
dst[255:192] := e3
dst[MAX:256] := 0
```
