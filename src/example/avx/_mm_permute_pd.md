`_mm_permute_pd(x: __m128d, imm8: int): __m128d`
================================================

> Shuffle double precision (64 bit) floating point elements in x using the control in imm8, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm_permute_pd (__m128d a, int imm8);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpermilpd xmm, xmm, imm8 |
| CPUID Flags | AVX                      |

## Operation

```
IF (imm8[0] == 0) dst[63:0] := a[63:0]; FI
IF (imm8[0] == 1) dst[63:0] := a[127:64]; FI
IF (imm8[1] == 0) dst[127:64] := a[63:0]; FI
IF (imm8[1] == 1) dst[127:64] := a[127:64]; FI
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
