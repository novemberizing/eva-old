`_mm256_unpackhi_epi32(x: __m256i, y: __m256i): __m256i`
========================================================

> Unpack and interleave 32 bit integers from the high half of each 128 bit lanein x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpackhi_epi32 (__m256i a, __m256i b);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpunpckhdq ymm, ymm, ymm |
| CPUID Flags | AVX2                     |

## Operation

```
DEFINE INTERLEAVE_HIGH_DWORDS(src1[127:0], src2[127:0]) {
	dst[31:0] := src1[95:64] 
	dst[63:32] := src2[95:64] 
	dst[95:64] := src1[127:96] 
	dst[127:96] := src2[127:96] 
	RETURN dst[127:0]	
}
dst[127:0] := INTERLEAVE_HIGH_DWORDS(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_HIGH_DWORDS(a[255:128], b[255:128])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
