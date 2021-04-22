`_mm256_insertf128_si256(x: __m256i, y: __m256i, imm8: int): __m256i`
=====================================================================

> Copy x to destination, then insert 128 bits from y into destination at the location specified by imm8.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_insertf128_si256 (__m256i a, __m128i b, int imm8);
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
