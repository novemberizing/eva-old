`_mm256_castsi256_pd(x: __m256i): __m256d`
==========================================

> Cast vector of type __m256i to type __m256d. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_castsi256_pd(__m256i x);
```
| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
