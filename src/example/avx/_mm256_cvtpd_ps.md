`_mm256_cvtpd_ps(x: __m256d): __m128`
=====================================

> Convert packed double precision (64 bit) floating point elements in x to packed single precision (32 bit) floating point lements, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm256_cvtpd_ps(__m256d x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vcvtpd2ps xmm, ymm |
| CPUID Flags | AVX                |

## Operation

```
FOR j := 0 to 3
	i := 32*j
	k := 64*j
	dst[i+31:i] := Convert_FP64_To_FP32(a[k+63:k])
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 1                |
| Skylake      | 7       | 1                |
| Broadwell    | 6       | 1                |
| Haswell      | 6       | 1                |
| Ivy Bridge   | 4       | 1                |
