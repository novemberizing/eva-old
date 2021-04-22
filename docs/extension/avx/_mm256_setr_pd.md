`_mm256_setr_pd(e3: double, e2: double, e1: double, e0: double): __m256d`
=========================================================================

> Set packed double precision (64 bit) floating point elements in destination with the supplied values in reverse order.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_setr_pd (double e3, double e2, double e1, double e0);
```

## Operation

```
dst[63:0] := e3
dst[127:64] := e2
dst[191:128] := e1
dst[255:192] := e0
dst[MAX:256] := 0
```
