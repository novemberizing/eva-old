`_mm256_loadu2_m128i(hi: __m128i const *, lo: __m128i const *): __m256i`
========================================================================

> Load two 128 bit values (composed of integer data) from memory, and combine them into a 256 bit value in destination. high address and low address do not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_loadu2_m128i (__m128i const* hiaddr, __m128i const* loaddr);
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

