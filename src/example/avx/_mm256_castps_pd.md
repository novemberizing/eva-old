`_mm256_castps_pd(x: __m256): __m256d`
======================================

> Cast vector of type __m256 to type __m256d. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_castps_pd(__m256 x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
