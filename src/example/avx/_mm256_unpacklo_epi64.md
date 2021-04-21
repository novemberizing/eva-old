`_mm256_unpacklo_epi64(x: __m256i, y: __m256i): __m256i`
========================================================

> Unpack and interleave 64 bit integers from the low half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpacklo_epi64 (__m256i a, __m256i b);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpunpcklqdq ymm, ymm, ymm |
| CPUID Flags | AVX2                      |

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
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
