`_mm256_storeu2_m128i(h: __m128i *, l: __m128i, x: __m256i)`
============================================================

> Store the high and low 128 bit halves (each composed of integer data) from x into memory two different 128 bit locations. high address and low address do not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

void _mm256_storeu2_m128i (__m128i* hiaddr, __m128i* loaddr, __m256i a);
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

