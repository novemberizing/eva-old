`_mm256_sign_epi8(x: __m256i, y: __m256i): __m256i`
===================================================

> Negate packed signed 8 bit integers in x when the corresponding signed 8 bit integer in y is negative, and store the results in destination. Element in destination are zeroed out when the corresponding element in y is zero.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sign_epi8 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsignb ymm, ymm, ymm |
| CPUID Flags | AVX2                  |


## Operation

```
FOR j := 0 to 31
	i := j*8
	IF b[i+7:i] < 0
		dst[i+7:i] := -(a[i+7:i])
	ELSE IF b[i+7:i] == 0
		dst[i+7:i] := 0
	ELSE
		dst[i+7:i] := a[i+7:i]
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
