`_mm256_blend_pd(x: __m256d, y: __m256d, imm8: const int): __m256d`
===================================================================

> Blend packed double precision (64 bit) floating point elements from x and y using control mask imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_blend_pd (__m256d x, __m256d y, const int imm8);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendpd ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                          |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF imm8[j]
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
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |
| Ivy Bridge   | 1       | 0.5              |
