`_mm256_abs_epi16(x: __m256i): __m256i`
=======================================

> Compute the absolute value of packed signed 16 bit integers in x, and store the unsigned results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_abs_epi16(__m256i x);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vpabsw ymm, ymm |
| CPUID Flags | AVX2            |

## Operation

```
FOR j := 0 to 15
    i := j*16
    dst[i+15:i] := ABS(a[i+15:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |

