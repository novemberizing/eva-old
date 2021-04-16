`_mm256_extract_epi16(x: __m256i, index: const int): int`
=========================================================

> Extract a 16 bit integer from x, selected with index, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

int _mm256_extract_epi16(__m256i a, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX2        |

## Operation

```
dst[15:0] := (a[255:0] >> (index[3:0] * 16))[15:0]
``
