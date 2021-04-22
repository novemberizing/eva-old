`_mm256_movedup_pd(x: __m256d): __m256d`
========================================

> Duplicate even indexed double precision (64 bit) floating point elements from x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_movedup_pd (__m256d a);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovddup ymm, ymm |
| CPUID Flags | AVX               |

## Operation

```
dst[63:0] := a[63:0]
dst[127:64] := a[63:0]
dst[191:128] := a[191:128]
dst[255:192] := a[191:128]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
