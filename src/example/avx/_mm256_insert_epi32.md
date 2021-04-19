`_mm256_insert_epi32(x: __m256i, i: int, index: const int): __m256i`
====================================================================

> Copy x to destination, and insert the 32 bit integer i into destination at the location specified by index.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_insert_epi32(__m256i a, __int32 i, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[255:0] := a[255:0]
sel := index[2:0]*32
dst[sel+31:sel] := i[31:0]
```
