`_mm256_extractf128_pd(x: __m256d, imm8: const int): __m128d`
=============================================================

> Extract 128 bits (composed of 2 packed double-precision (64-bit) floating-point elements) from x, selected with imm8, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm256_extractf128_pd (__m256d a, const int imm8);
```

| -           | Description                 |
| ----------- | --------------------------- |
| Instruction | vextractf128 xmm, ymm, imm8 |
| CPUID Flags | AVX                         |

## Operation

```
CASE imm8[0] OF
0: dst[127:0] := a[127:0]
1: dst[127:0] := a[255:128]
ESAC
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |
