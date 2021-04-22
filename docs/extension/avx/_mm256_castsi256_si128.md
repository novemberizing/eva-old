`_mm256_castsi256_si128(x: __m256i): __m128i`
=============================================

> Cast vector of type __m256i to type __m128i. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm256_castsi256_si128(__m256i x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

