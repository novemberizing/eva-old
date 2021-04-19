`_mm256_insert_epi16(x: __m256i, i: short, index: const int): __m256i`
======================================================================

> Copy x to destination, and insert the 16 bit integer i into destination at the location specified by index.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_insert_epi16 (__m256i a, __int16 i, const int index)
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[255:0] := a[255:0]
sel := index[3:0]*16
dst[sel+15:sel] := i[15:0]
```

