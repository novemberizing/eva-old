`_mm256_blend_ps(x: __m256, y: __m256): __m256`
===============================================

> Blend packed single precision (32 bit) floating point elements from x and y using control mask imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_blend_ps(__m256 x, __m256 y, const int imm8);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendps ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                          |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF imm8[j]
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
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |
| Ivy Bridge   | 1       | 0.5              |

