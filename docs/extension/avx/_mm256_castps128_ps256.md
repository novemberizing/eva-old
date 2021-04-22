`_mm256_castps128_ps256(x: __m128): __m256`
===========================================

> Cast vector of type __m128 to type __m256; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not genrate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_castps128_ps256(__m128 x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
