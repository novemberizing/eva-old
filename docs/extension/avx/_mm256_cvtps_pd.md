`_mm256_cvtps_pd(x: __m128): __m256d`
=====================================

> Convert packed single precision (32 bit) floating point elements in x to packed double precision (64 bit) floating point elements, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_cvtps_pd(__m128 x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vcvtps2pd ymm, xmm |
| CPUID Flags | AVX                |

## Operation

```
FOR j := 0 to 3
	i := 64*j
	k := 32*j
	dst[i+63:i] := Convert_FP32_To_FP64(a[k+31:k])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 1                |
| Skylake      | 7       | 1                |
| Broadwell    | 4       | 1                |
| Haswell      | 4       | 1                |
| Ivy Bridge   | 2       | 1                |
