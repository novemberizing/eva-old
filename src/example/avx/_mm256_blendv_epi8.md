`_mm256_blendv_epi8(x: __m256i, y: __m256i, mask: __m256i): __m256i`
====================================================================

> Blend packed 8 bit integers from x and y using mask, and store the results int destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_blendv_epi8(__m256i x, __m256i y, __m256i mask);
```

| - | 