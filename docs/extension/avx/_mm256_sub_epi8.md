`_mm256_sub_epi8(x: __m256i, y: __m256i): __m256i`
==================================================

> Subtract packed 8 bit integers in y from packed 8 bit integers in x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sub_epi8 (__m256i a, __m256i b);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsubb ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := a[i+7:i] - b[i+7:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
