`_mm256_unpackhi_pd(x: __m256d, y: __m256d): __m256d`
=====================================================

> Unpack and interleave double precision (64 bit) floating point elements from the high half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_unpackhi_pd (__m256d a, __m256d b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vunpckhpd ymm, ymm, ymm |
| CPUID Flags | AVX                     |

## Operation

```
DEFINE INTERLEAVE_HIGH_QWORDS(src1[127:0], src2[127:0]) {
	dst[63:0] := src1[127:64] 
	dst[127:64] := src2[127:64] 
	RETURN dst[127:0]	
}
dst[127:0] := INTERLEAVE_HIGH_QWORDS(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_HIGH_QWORDS(a[255:128], b[255:128])
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
