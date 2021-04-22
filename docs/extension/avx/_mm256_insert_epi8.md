`_mm256_insert_epi8(x: __m256i, i: char, index: const int): __m256i`
====================================================================

> Copy x to destination, and insert the 8 bit integer i into destination at the location specified by index.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_insert_epi8 (__m256i a, __int8 i, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[255:0] := a[255:0]
sel := index[4:0]*8
dst[sel+7:sel] := i[7:0]
```

