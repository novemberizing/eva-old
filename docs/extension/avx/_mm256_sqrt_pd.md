`_mm256_sqrt_pd(x: __m256d): __m256d`
=====================================

> Compute the square root of packed double precision (64 bit) floating point elements in x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_sqrt_pd (__m256d a);
```

| -           | Description      |
| ----------- | ---------------- |
| Instruction | vsqrtpd ymm, ymm |
| CPUID Flags | AVX              |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := SQRT(a[i+63:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture    | Latency | Throughput (CPI) |
| --------------- | ------- | ---------------- |
| Skylake         | 18      | 12               |
| Knights Landing | 38      | ~10              |
| Broadwell       | 19-35   | 16-27            |
| Haswell         | 19-35   | 16-27            |
| Ivy Bridge      | 19-35   | 28               |
