`_mm256_max_epi32(x: __m256i, y: __m256i): __m256i`
===================================================

> Compare packed signed 32 bit integers in x and y, and store packed maximum values in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_max_epi32 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpmaxsd ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := MAX(a[i+31:i], b[i+31:i])
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
