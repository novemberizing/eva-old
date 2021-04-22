`_mm256_mul_pd(x: __m256d, y: __m256d): __m256d`
================================================

> Multiply packed double precision (64 bit) floating point elements in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_mul_pd (__m256d a, __m256d b);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vmulpd ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[i+63:i] * b[i+63:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 0.5              |
| Haswell      | 5       | 0.5              |
| Ivy Bridge   | 5       | 1                |
