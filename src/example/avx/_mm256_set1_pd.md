`_mm256_set1_pd(x: double): __m256d`
====================================

> Broadcast double precision (64 bit) floating point value x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_set1_pd (double x);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[63:0]
ENDFOR
dst[MAX:256] := 0
```