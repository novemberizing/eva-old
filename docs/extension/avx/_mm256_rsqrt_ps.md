`_mm256_rsqrt_ps(x: __m256): __m256`
====================================

> Compute the approximate reciprocal square root of packed single precision (32 bit) floating point elements in x, and store the results in destination. The maximum relative error for this approximation is less than 1.5*2^-12.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_rsqrt_ps (__m256 x);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vrsqrtps ymm, ymm |
| CPUID Flags | AVX               |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := (1.0 / SQRT(a[i+31:i]))
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 1                |
| Skylake      | 4       | 1                |
| Broadwell    | 7       | 2                |
| Haswell      | 7       | 2                |
| Ivy Bridge   | 7       | 2                |
