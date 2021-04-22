`_mm256_cvtepi32_pd(x: __m128i): __m256i`
=========================================

> Convert packed signed 32 bit integers in x to packed double precision (64 bit) floating point elements, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_cvtepi32_pd(__m128i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vcvtdq2pd ymm, xmm |
| CPUID Flags | AVX                |

## Operation

```
FOR j := 0 to 3
	i := j*32
	m := j*64
	dst[m+63:m] := Convert_Int32_To_FP64(a[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 1                |
| Skylake      | 7       | 1                |
| Broadwell    | 6       | 1                |
| Haswell      | 6       | 1                |
| Ivy Bridge   | 4       | 1                |
