`_mm256_castpd_ps(x: __256d): __m256`
=====================================

> Cast vector of type __m256d to type __m256. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_castpd_ps(__m256d x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
