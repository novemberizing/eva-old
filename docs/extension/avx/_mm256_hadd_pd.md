`_mm256_hadd_pd(x: __m256d, y: __m256d): __m256d`
=================================================

> Horizontally add adjacent pairs of double precision (64 bit) floating point elements in x and y, and pack the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_hadd_pd(__m256d x, __m256d y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vhaddpd ymm, ymm, ymm |
| CPUID Flags | AVX                   |

## Operation

```
dst[63:0] := a[127:64] + a[63:0]
dst[127:64] := b[127:64] + b[63:0]
dst[191:128] := a[255:192] + a[191:128]
dst[255:192] := b[255:192] + b[191:128]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 6       | 2                |
| Skylake      | 7       | 2                |
