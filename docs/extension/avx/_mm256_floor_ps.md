`_mm256_floor_ps(x: __m256): __m256`
====================================

> Round the packed single precision (32 bit) floating point elements in a down to an integer value, and store the results as packed single precision floating point elements in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_floor_ps(__m256 x);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vroundps ymm, ymm, imm8 |
| CPUID Flags | AVX                     |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := FLOOR(a[i+31:i])
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
