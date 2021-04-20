`_mm256_loadu2_m128d(hi: double const *, lo: double const *): __m256d`
======================================================================

> Load two 128 bit values (composed of 2 packed double precision (64 bit) floating point elements) from memory, and combine them into a 256 bit value in destination. high address and low address do not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_loadu2_m128d (double const* hiaddr, double const* loaddr);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[127:0] := MEM[loaddr+127:loaddr]
dst[255:128] := MEM[hiaddr+127:hiaddr]
dst[MAX:256] := 0
```