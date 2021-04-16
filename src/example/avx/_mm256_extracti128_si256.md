`_mm256_extracti128_si256(x: __m256i, imm8: const int): __m128i`
================================================================

> Extract 128 bits (composed of integer data) from x, selected with imm8, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm256_extracti128_si256 (__m256i a, const int imm8)
```

| -           | Description                 |
| ----------- | --------------------------- |
| Instruction | vextracti128 xmm, ymm, imm8 |
| CPUID Flags | AVX2                        |

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
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
