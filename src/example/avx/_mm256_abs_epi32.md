`_mm256_abs_epi32(x: __m256i): __m256i`
=======================================

> Compute the absolute value of packed signed 32 bit integers in a, and store the unsigned results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_abs_epi32(__m256i x);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vpabsd ymm, ymm |
| CPUID Flags | AVX2            |

## Operation

```
FOR j := 0 to 7
    i := j * 32
    dst[i+31:i] := ABS(a[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |

