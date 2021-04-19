`_mm256_hadd_epi32(x: __m256i, y: __m256i): __m256i`
====================================================

> Horizontally add adjacent pairs of 32 bit integers in x and y, and pack the signed 32 bit results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_hadd_epi32(__m256i x, __m256i y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vphaddd ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
dst[31:0] := a[63:32] + a[31:0]
dst[63:32] := a[127:96] + a[95:64]
dst[95:64] := b[63:32] + b[31:0]
dst[127:96] := b[127:96] + b[95:64]
dst[159:128] := a[191:160] + a[159:128]
dst[191:160] := a[255:224] + a[223:192]
dst[223:192] := b[191:160] + b[159:128]
dst[255:224] := b[255:224] + b[223:192]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 3       | 2                |
| Broadwell    | 3       | 2                |
| Haswell      | 3       | 2                |
