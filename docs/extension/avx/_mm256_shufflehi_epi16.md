`_mm256_shufflehi_epi16(x: __m256i, imm8: const int): __m256i`
==============================================================

> Shuffle 16 bit integers in the high 64 bits of 128 bit lanes of x using the control in imm8. Store the results in the high 64 bits of 128 bit lanes of destination, with the low 64 bits of 128 bits lanes being copied from x to destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_shufflehi_epi16 (__m256i a, const int imm8);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpshufhw ymm, ymm, imm8 |
| CPUID Flags | AVX2                    |

## Operation

```
dst[63:0] := a[63:0]
dst[79:64] := (a >> (imm8[1:0] * 16))[79:64]
dst[95:80] := (a >> (imm8[3:2] * 16))[79:64]
dst[111:96] := (a >> (imm8[5:4] * 16))[79:64]
dst[127:112] := (a >> (imm8[7:6] * 16))[79:64]
dst[191:128] := a[191:128]
dst[207:192] := (a >> (imm8[1:0] * 16))[207:192]
dst[223:208] := (a >> (imm8[3:2] * 16))[207:192]
dst[239:224] := (a >> (imm8[5:4] * 16))[207:192]
dst[255:240] := (a >> (imm8[7:6] * 16))[207:192]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
