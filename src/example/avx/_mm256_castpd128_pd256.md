`_mm256_castpd128_pd256(x: __m128d): __m256d`
=============================================

> Cast vector of type __m128d to type __m256d; the upper 128 bits of the result are undefined. This intrinsic is only for compilation and does tno generate any instructions, thus is has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_castpd128_pd256(__m128d x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
