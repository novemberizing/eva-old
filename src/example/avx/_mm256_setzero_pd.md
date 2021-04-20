`_mm256_setzero_pd(): __m256d`
==============================

> Return vector of type __m256d with all elements set to zero.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_setzero_pd (void);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vxorpd ymm, ymm, ymm |
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
