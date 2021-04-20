`_mm256_set1_epi64x(x: long long): __m256i`
===========================================

> Broadcast 64 bit integer x to all elements of destination. This intrinsic may generate the vpbroadcastq.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set1_epi64x (long long a);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[63:0]
ENDFOR
dst[MAX:256] := 0
```

