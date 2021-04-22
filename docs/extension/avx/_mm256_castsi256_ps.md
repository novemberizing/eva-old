`_mm256_castsi256_ps(x: __m256i): __m256`
=========================================

> Cast vector of type __m256i to type __m256. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_castsi256_ps(__m256i x);
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
