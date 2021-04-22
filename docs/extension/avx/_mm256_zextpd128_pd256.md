`_mm256_zextpd128_pd256(x: __m128d): __m256d`
=============================================

> Cast vector of type __m128d to type __m256d; the upper 128 bits of the result are zeroed. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_zextpd128_pd256 (__m128d a);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
