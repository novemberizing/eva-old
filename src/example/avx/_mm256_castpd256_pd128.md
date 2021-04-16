`_mm256_castpd256_pd128(x: __m256d): __m128d`
=============================================

> Cast vector of type __m256d to type __m128d. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm256_castpd256_pd128(__m256d x);
```

