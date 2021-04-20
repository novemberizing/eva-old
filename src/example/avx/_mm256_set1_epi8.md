`_mm256_set1_epi8 (x: char): __m256i`
=====================================

> Broadcast 8 bit integer x to all elements of destination. This intrinsic may generate the vpbroadcastb.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set1_epi8 (char a);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := a[7:0]
ENDFOR
dst[MAX:256] := 0
```
