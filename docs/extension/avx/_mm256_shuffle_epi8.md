`_mm256_shuffle_epi8(x: __m256i, y: __m256i): __m256i`
======================================================

> Shuffle 8 bit integers in x within 128 bit lanes according to shuffle control mask in the corresponding 8 bit element of y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_shuffle_epi8 (__m256i x, __m256i y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpshufb ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 15
	i := j*8
	IF b[i+7] == 1
		dst[i+7:i] := 0
	ELSE
		index[3:0] := b[i+3:i]
		dst[i+7:i] := a[index*8+7:index*8]
	FI
	IF b[128+i+7] == 1
		dst[128+i+7:128+i] := 0
	ELSE
		index[3:0] := b[128+i+3:128+i]
		dst[128+i+7:128+i] := a[128+index*8+7:128+index*8]
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
