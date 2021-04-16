`_mm256_extract_epi64(x: __m256i, index: const int): __int64`
=============================================================

> Extract a 64 bit integer from x, selected with index, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__int64 _mm256_extract_epi64(__m256i a, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[63:0] := (a[255:0] >> (index[1:0] * 64))[63:0]
```
