`_mm256_castpd_si256(x: __m256d): __m256i`
==========================================

> Cast vector of type __m256d to type __m256i. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_castpd_si256(__m256d x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
