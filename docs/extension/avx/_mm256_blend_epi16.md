`_mm256_blend_epi16(x: __m256i, y: __m256i, imm8: const int): __m256i`
======================================================================

> Blend packed 16 bit integers from x and y within 128 bit lanes using control mask imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_blend_epi16(__m256i x, __m256i y, const int imm8);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vpblendw ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX2                         |

## Operation

```
FOR j := 0 to 15
	i := j*16
	IF imm8[j%8]
		dst[i+15:i] := b[i+15:i]
	ELSE
		dst[i+15:i] := a[i+15:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
