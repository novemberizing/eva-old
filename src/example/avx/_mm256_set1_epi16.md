`_mm256_set1_epi16(x: short): __m256i`
======================================

> Broadcast 16 bit integer x to all, all elements of destination. This intrinsic may generate the vpbroadcastw.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set1_epi16 (short x);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
FOR j := 0 to 15
	i := j*16
	dst[i+15:i] := a[15:0]
ENDFOR
dst[MAX:256] := 0
```
