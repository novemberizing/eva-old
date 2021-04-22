`_mm256_setr_m128i(l: __m128i, h: __m128i): __m256i`
====================================================

> Set packed __m256i vector destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_setr_m128i (__m128i lo, __m128i hi);
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
