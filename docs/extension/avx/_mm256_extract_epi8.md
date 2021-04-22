`_mm256_extract_epi8(x: __m256i, index: const int): int`
========================================================

> Extract an 8 bit integer from x, selected with index, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

int _mm256_extract_epi8(__m256i x, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX2        |

## Operation

```
dst[7:0] := (a[255:0] >> (index[4:0] * 8))[7:0]
```
