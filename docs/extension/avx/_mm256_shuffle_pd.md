`_mm256_shuffle_pd(x: __m256d, imm8: const int): __m256d`
=========================================================

> Shuffle double precision (64 bit) floating point elements within 128 bit lanes using the control in imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_shuffle_pd (__m256d a, __m256d b, const int imm8);
```

| -           | Description                 |
| ----------- | --------------------------- |
| Instruction | vshufpd ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                         |

## Operation

```
dst[63:0] := (imm8[0] == 0) ? a[63:0] : a[127:64]
dst[127:64] := (imm8[1] == 0) ? b[63:0] : b[127:64]
dst[191:128] := (imm8[2] == 0) ? a[191:128] : a[255:192]
dst[255:192] := (imm8[3] == 0) ? b[191:128] : b[255:192]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
