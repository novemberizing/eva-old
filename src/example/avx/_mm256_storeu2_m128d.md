`_mm256_storeu2_m128d(h: double *, l: double *, x: __m256d)`
============================================================

> Store the high and low 128 bit halves (each composed of 2 packed precision (64 bit) floating point elements) from x into memory two different 128 bit locations. high address and low address do not need to be aligned on any paritcular boundary.

## Synopsis

```c
#include <immintrin.h>

void _mm256_storeu2_m128d (double* hiaddr, double* loaddr, __m256d a);
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