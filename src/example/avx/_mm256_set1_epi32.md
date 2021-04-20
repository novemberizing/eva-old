`_mm256_set1_epi32(x: int): __m256i`
====================================

> Broadcast 32 bit integere x to all elements of destination. This intrinsic may generate the vpbroadcastd.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set1_epi32 (int a);
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
