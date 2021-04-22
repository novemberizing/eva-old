`_mm256_abs_epi8(x: __m256i): __m256i`
======================================

> Compute the absolute value of packed signed 8 bit integers in x, and store the unsigned results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_abs_epi8(__m256i x);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vpabsb ymm, ymm |
| CPUID Flags | AVX2            |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := ABS(a[i+7:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
