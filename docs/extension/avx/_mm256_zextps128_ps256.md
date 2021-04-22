`_mm256_zextps128_ps256(x: __m128): __m256`
===========================================

> Cast vector of type __m128 to __m256; the upper 128 bits of the result are zeroed. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_zextps128_ps256 (__m128 a);
```

| -          | Description |
| ---------- | ----------- |
| CPUID Flags| AVX         |
