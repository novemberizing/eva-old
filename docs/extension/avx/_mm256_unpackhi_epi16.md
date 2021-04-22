`_mm256_unpackhi_epi16(x: __m256i, y: __m256i): __m256i`
========================================================

> Unpack and interleave 16 bit integers from the high half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpackhi_epi16 (__m256i a, __m256i b);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpunpckhwd ymm, ymm, ymm |
| CPUID Flags | AVX2                     |

## Operation

```
DEFINE INTERLEAVE_HIGH_WORDS(src1[127:0], src2[127:0]) {
	dst[15:0] := src1[79:64]
	dst[31:16] := src2[79:64] 
	dst[47:32] := src1[95:80] 
	dst[63:48] := src2[95:80] 
	dst[79:64] := src1[111:96] 
	dst[95:80] := src2[111:96] 
	dst[111:96] := src1[127:112] 
	dst[127:112] := src2[127:112] 
	RETURN dst[127:0]
}
dst[127:0] := INTERLEAVE_HIGH_WORDS(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_HIGH_WORDS(a[255:128], b[255:128])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
