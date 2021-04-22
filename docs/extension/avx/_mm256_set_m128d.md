`_mm256_set_m128d(h: __m128d, l: __m128d): __m256d`
===================================================

> Set packed __m256d vector destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_set_m128d (__m128d hi, __m128d lo);
```

| -           | Description                     |
| ----------- | ------------------------------- |
| Instruction | vinsertf128 ymm, ymm, xmm, imm8 |
| CPUID Flags | AVX                             |

## Operation

```
dst[127:0] := lo[127:0]
dst[255:128] := hi[127:0]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |
