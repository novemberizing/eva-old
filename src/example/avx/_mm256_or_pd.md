`_mm256_or_pd (x: __m256d, y: __m256d): __m256d`
================================================

> Compute bitwise OR of packed double precision (64 bit) floating point elements in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_or_pd (__m256d a, __m256d b);
```

| -           | Description         |
| ----------- | ------------------- |
| Instruction | vorpd ymm, ymm, ymm |
| CPUID Flags | AVX                 |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[i+63:i] OR b[i+63:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
