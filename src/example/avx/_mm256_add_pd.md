`_mm256_add_pd(x: __m256d, y: __m256d): __m256d`
================================================

> Add packed double precision (64 bit) floating point elements in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_add_pd(__m256d x, __m256d y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vaddpd ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[i+63:i] + b[i+63:i]
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
