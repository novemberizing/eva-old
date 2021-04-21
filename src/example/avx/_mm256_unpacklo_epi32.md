`_mm256_unpacklo_epi32(x: __m256i, y: __m256i): __m256i`
========================================================

> Unpack and interleave 32 bit integers from the low half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpacklo_epi32 (__m256i a, __m256i b);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpunpckldq ymm, ymm, ymm |
| CPUID Flags | AVX2                     |

## Operation

```
DEFINE INTERLEAVE_DWORDS(src1[127:0], src2[127:0]) {
	dst[31:0] := src1[31:0] 
	dst[63:32] := src2[31:0] 
	dst[95:64] := src1[63:32] 
	dst[127:96] := src2[63:32] 
	RETURN dst[127:0]	
}
dst[127:0] := INTERLEAVE_DWORDS(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_DWORDS(a[255:128], b[255:128])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
