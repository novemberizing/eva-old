`_mm256_floor_pd(x: __m256d): __m256d`
======================================

> Round the packed double precision (64 bit) floating point elements in a down to an integer value, and store the results as packed double precision floating point elements in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_floor_pd(__m256d x);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vroundpd ymm, ymm, imm8 |
| CPUID Flags | AVX                     |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := FLOOR(a[i+63:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 8       | 1                |
| Skylake      | 8       | 1                |
| Broadwell    | 6       | 2                |
| Haswell      | 6       | 2                |
| Ivy Bridge   | 3       | 1                |

