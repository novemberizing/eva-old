`_mm256_blendv_pd(x: __m256d, y: __m256d, mask: __m256d): __m256d`
==================================================================

> Blend packed double precision (64 bit) floating point elements from x and y using mask, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_blendv_pd(__m256d x, __m256d y, __m256d mask);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendvpd ymm, ymm, ymm, ymm |
| CPUID Flags | AVX                          |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF mask[i+63]
		dst[i+63:i] := b[i+63:i]
	ELSE
		dst[i+63:i] := a[i+63:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 2       | 0.66             |
| Broadwell    | 2       | 2                |
| Haswell      | 2       | 2                |
| Ivy Bridge   | 1       | 1                |
