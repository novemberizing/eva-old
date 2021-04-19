`_mm256_inserti128_si256(x: __m256i, y: __m128i, imm8: const int): __m256i`
===========================================================================

> Copy x to destination, then insert 128 bits (composed of integer data) from y into destination at the location specified by imm8.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_inserti128_si256 (__m256i a, __m128i b, const int imm8);
```

| -           | Description                     |
| ----------- | ------------------------------- |
| Instruction | vinserti128 ymm, ymm, xmm, imm8 |
| CPUID Flags | AVX2                            |

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
