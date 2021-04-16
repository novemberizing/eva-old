`_mm256_extract_epi32(x: __m256i, index: const int): __int32`
=============================================================

> Extract a 32 bit integer from x, selected with index, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__int32 _mm256_extract_epi32(__m256i x, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[31:0] := (a[255:0] >> (index[2:0] * 32))[31:0]
```
