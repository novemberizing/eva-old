`_mm256_unpackhi_epi64(x: __m256i, y: __m256i): __m256i`
========================================================

> Unpack and interleave 64 bit integers from the high half of each 128 bit lane in x and y, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpackhi_epi64 (__m256i a, __m256i b);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpunpckhqdq ymm, ymm, ymm |
| CPUID Flags | AVX2                      |

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
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
