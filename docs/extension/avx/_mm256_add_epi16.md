`_mm256_add_epi16(x: __m256i, y: __m256i): __m256i`
===================================================

> Add packed 16 bit integers in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_add_epi16(__m256i x, __m256i y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpaddw ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 15
	i := j*16
	dst[i+15:i] := a[i+15:i] + b[i+15:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
