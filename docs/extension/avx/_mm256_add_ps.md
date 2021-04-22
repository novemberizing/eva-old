`_mm256_add_ps(x: __m256, y: __m256): __m256`
=============================================

> Add packed single precision (32 bit) floating point elements in x and y, store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_add_ps(__m256 x, __m256 y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vaddps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[i+31:i] + b[i+31:i]
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
