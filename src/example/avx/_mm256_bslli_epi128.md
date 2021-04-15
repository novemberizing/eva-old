`_mm256_bslli_epi128(x: __m256i, imm8: const int): __m256i`
===========================================================

> Shift 128 bit lanes in x left by imm8 bytes while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_bslli_epi128 (__m256i x, const int imm8);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpslldq ymm, ymm, imm8 |
| CPUID Flags | AVX2                   |

## Operation

```
tmp := imm8[7:0]
IF tmp > 15
	tmp := 16
FI
dst[127:0] := a[127:0] << (tmp*8)
dst[255:128] := a[255:128] << (tmp*8)
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
