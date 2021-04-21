`_mm256_subs_epu16(x: __m256i, y: __m256i): __m256i`
====================================================

> Subtract packed unsigned 16 bit integers in y from packed unsigned 16 bit integers in x using satuation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_subs_epu16 (__m256i a, __m256i b);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpsubusw ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 15
	i := j*16
	dst[i+15:i] := SaturateU16(a[i+15:i] - b[i+15:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
