`_mm256_sign_epi32(x: __m256i, y: __m256i): __m256i`
====================================================

> Negate packed signed 32 bit integers in x when the corresponding signed 32 bit integer in y is negative, and store the results in destination. Element in destination are zeroed out when the corresponding element in y is zero.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sign_epi32 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsignd ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF b[i+31:i] < 0
		dst[i+31:i] := -(a[i+31:i])
	ELSE IF b[i+31:i] == 0
		dst[i+31:i] := 0
	ELSE
		dst[i+31:i] := a[i+31:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
