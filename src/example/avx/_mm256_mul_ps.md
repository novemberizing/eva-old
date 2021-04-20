`_mm256_mul_ps (x: __m256, y: __m256): __m256`
==============================================

> Multiply packed single precision (32 bit) floating point elements in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_mul_ps (__m256 a, __m256 b)
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vmulps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[i+31:i] * b[i+31:i]
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
