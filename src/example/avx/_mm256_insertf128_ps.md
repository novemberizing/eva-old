`_mm256_insertf128_ps(x: __m256, y: __m128, imm8: int): __m256`
===============================================================

> Copy x to destination, then insert 128 bits (composed of 4 packed single precision (32 bit) floating point elements) from b into destination at the location specified by imm8.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_insertf128_ps(__m256 a, __m128 b, int imm8);
```

| -           | Description                     |
| ----------- | ------------------------------- |
| Instruction | vinsertf128 ymm, ymm, xmm, imm8 |
| CPUID Flags | AVX                             |

## Operation

```
dst[255:0] := a[255:0]
CASE (imm8[0]) OF
0: dst[127:0] := b[127:0]
1: dst[255:128] := b[127:0]
ESAC
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
