`_mm256_blendv_ps(x: __m256, y: __m256, mask: __m256): __m256`
==============================================================

> Blend packed single precision (32 bit) floating point elements from x and y using mask, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_blendv_ps(__m256 x, __m256 y, __m256 mask);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendvps ymm, ymm, ymm, ymm |
| CPUID Flags | AVX                          |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF mask[i+31]
		dst[i+31:i] := b[i+31:i]
	ELSE
		dst[i+31:i] := a[i+31:i]
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
