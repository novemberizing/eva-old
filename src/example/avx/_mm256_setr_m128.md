`_mm256_setr_m128(l: __m128, h: __m128): __m256`
================================================

> Set packed __m256 vector destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_setr_m128 (__m128 lo, __m128 hi);
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