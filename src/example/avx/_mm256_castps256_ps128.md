`_mm256_castps256_ps128(x: __m256): __m128`
===========================================

> Cast vector of type __m256 to type __m128. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm256_castps256_ps128(__m256 x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
