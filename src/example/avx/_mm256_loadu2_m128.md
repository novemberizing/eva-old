`_mm256_loadu2_m128(hi: float const *, lo: float const *): __m256`
==================================================================

> Load two 128 bit values (composed of 4 packed single precision (32 bit) floating point elements) from memory, and combine them into a 256 bit value in destination. high address and low address do not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_loadu2_m128(float const* hi, float const* lo);
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
