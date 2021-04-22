`_mm256_cvtps_epi32(x: __m256): __m256i`
========================================

> Convert packed single precision (32 bit) floating point elements in x to packed 32 bit integers, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cvtps_epi32(__m256 x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vcvtps2dq ymm, ymm |
| CPUID Flags | AVX                |

## Operation

```
FOR j := 0 to 7
	i := 32*j
	dst[i+31:i] := Convert_FP32_To_Int32(a[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |
