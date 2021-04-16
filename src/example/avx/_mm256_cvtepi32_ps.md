`_mm256_cvtepi32_ps(x: __m256i): __m256`
========================================

> Convert packed signed 32 bit integers in x to packed single precision (32 bit) floating point elements, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_cvtepi32_ps(__m256i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vcvtdq2ps ymm, ymm |
| CPUID Flags | AVX                |

## Operation

```
FOR j := 0 to 7
	i := 32*j
	dst[i+31:i] := Convert_Int32_To_FP32(a[i+31:i])
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
