`_mm256_blendv_epi8(x: __m256i, y: __m256i, mask: __m256i): __m256i`
====================================================================

> Blend packed 8 bit integers from x and y using mask, and store the results int destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_blendv_epi8(__m256i x, __m256i y, __m256i mask);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vpblendvb ymm, ymm, ymm, ymm |
| CPUID Flags | AVX2                         |

## Operation

```
FOR j := 0 to 31
	i := j*8
	IF mask[i+7]
		dst[i+7:i] := b[i+7:i]
	ELSE
		dst[i+7:i] := a[i+7:i]
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
