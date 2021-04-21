`_mm256_unpacklo_pd(x: __m256d, y: __m256d): __m256d`
=====================================================

> Unpack and interleave double precision (64 bit) floating point elements from the low half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_unpacklo_pd (__m256d a, __m256d b);
```

## Operation

```
DEFINE INTERLEAVE_QWORDS(src1[127:0], src2[127:0]) {
	dst[63:0] := src1[63:0] 
	dst[127:64] := src2[63:0] 
	RETURN dst[127:0]
}
dst[127:0] := INTERLEAVE_QWORDS(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_QWORDS(a[255:128], b[255:128])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 1                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |

