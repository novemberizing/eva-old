`_mm256_set1_ps(x: float): __m256`
==================================

> Broadcast single precision (32 bit) floating point value x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_set1_ps (float a);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[31:0]
ENDFOR
dst[MAX:256] := 0
```
