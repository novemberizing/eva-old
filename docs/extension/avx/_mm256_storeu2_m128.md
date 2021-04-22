`_mm256_storeu2_m128(h: float *, l: float *, x: __m256)`
========================================================

> Store the high and low 128 bit halves (each composed of 4 packed single precision (32 bit) floating point elements) from x into memory two different 128 bit locations. high address and low address do not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

void _mm256_storeu2_m128 (float* hiaddr, float* loaddr, __m256 a);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
MEM[loaddr+127:loaddr] := a[127:0]
MEM[hiaddr+127:hiaddr] := a[255:128]
```

