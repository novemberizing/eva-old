`_mm256_setzero_ps(): __m256`
=============================

> Return vector of type __m256 with all elements set to zero.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_setzero_ps (void);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vxorps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
dst[MAX:0] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |

