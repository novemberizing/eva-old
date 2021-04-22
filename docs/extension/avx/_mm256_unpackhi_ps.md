`_mm256_unpackhi_ps(x: __m256, y: __m256): __m256`
==================================================

> Unpack and interleave single precision (32 bit) floating point elements from the high half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_unpackhi_ps (__m256 a, __m256 b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vunpckhps ymm, ymm, ymm |
| CPUID Flags | AVX                     |

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
| Icelake      | 1       | 1                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
