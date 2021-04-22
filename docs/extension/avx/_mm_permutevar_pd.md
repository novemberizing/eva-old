`_mm_permutevar_pd(x: __m128d, y: __m128i): __m128d`
====================================================

> Shuffle double precision (64 bit) floating point elements in x using the control in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm_permutevar_pd (__m128d a, __m128i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpermilpd xmm, xmm, xmm |
| CPUID Flags | AVX                     |

## Operation

```
IF (b[1] == 0) dst[63:0] := a[63:0]; FI
IF (b[1] == 1) dst[63:0] := a[127:64]; FI
IF (b[65] == 0) dst[127:64] := a[63:0]; FI
IF (b[65] == 1) dst[127:64] := a[127:64]; FI
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
