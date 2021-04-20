`_mm256_max_epu8(x: __m256i, y: __m256i): __m256i`
==================================================

> Compare packed unsigned 8 bit integers in x and y, and store packed maximum values in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_max_epu8 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpmaxub ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := MAX(a[i+7:i], b[i+7:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
