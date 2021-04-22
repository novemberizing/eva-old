`_mm256_insert_epi64(x: __m256i, i: long, index: int): __m256i`
===============================================================

> Copy x to destination, and insert the 64 bit integer i into destination at the location specified by index.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_insert_epi64 (__m256i a, __int64 i, const int index);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[255:0] := a[255:0]
sel := index[1:0]*64
dst[sel+63:sel] := i[63:0]
```
