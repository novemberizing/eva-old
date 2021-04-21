`_mm256_zextsi128_si256(x: __m128i): __m256i`
=============================================

> Cast vector of type __m128i to type __m256i; the upper 128 bits of the result are zeroed. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_zextsi128_si256 (__m128i a);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
