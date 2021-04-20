`_mm256_setzero_si256(): __m256i`
=================================

> Return vector of type __m256i with all elements set to zero.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_setzero_si256 (void);
```

| -           | Description         |
| ----------- | ------------------- |
| Instruction | vpxor ymm, ymm, ymm |
| CPUID Flags | AVX                 |

## Operation

```
dst[MAX:0] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |

