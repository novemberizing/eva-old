`_mm256_cvttpd_epi32(x: __m256d): __m128i`
==========================================

> Convert packed double precision (64 bit) floating point elements in x to packed 32 bit integers with truncation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm256_cvttpd_epi32(__m256d x);
```

| -           | Description         |
| ----------- | ------------------- |
| Instruction | vcvttpd2dq xmm, ymm |
| CPUID Flags | AVX                 |

## Operation

```
FOR j := 0 to 3
	i := 32*j
	k := 64*j
	dst[i+31:i] := Convert_FP64_To_Int32_Truncate(a[k+63:k])
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
