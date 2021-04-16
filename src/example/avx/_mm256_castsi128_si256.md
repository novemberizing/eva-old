`_mm256_castsi128_si256(x: __m128i): __m256i`
=============================================

> Cast vector of tyhpe __m128i to type __m256i; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_castsi128_si256(__m128i x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |