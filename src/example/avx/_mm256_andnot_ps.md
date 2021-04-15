`_mm256_andnot_ps(x: __m256, y: __m256): __m256`
================================================

> Compute the bitwise NOT of packed single precision (32 bit) floating point elements in x and then AND with y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_andnot_ps(__m256 x, __m256 y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vandnps ymm, ymm, ymm |
| CPUID Flags | AVX                   |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := ((NOT a[i+31:i]) AND b[i+31:i])
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
