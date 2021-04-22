`_mm256_sqrt_ps(x: __m256): __m256`
===================================

> Compute the square root of packed single precision (32 bit) floating point elements in x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_sqrt_ps (__m256 a);
```

| -           | Description      |
| ----------- | ---------------- |
| Instruction | vsqrtps ymm, ymm |
| CPUID Flags | AVX              |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := SQRT(a[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture    | Latency | Throughput (CPI) |
| --------------- | ------- | ---------------- |
| Icelake         | 12      | 6                |
| Skylake         | 12      | 6                |
| Knights Landing | 38      | ~10              |
| Broadwell       | 18-21   | 13               |
| Haswell         | 18-21   | 13               |
| Ivy Bridge      | 18-21   | 14               |
