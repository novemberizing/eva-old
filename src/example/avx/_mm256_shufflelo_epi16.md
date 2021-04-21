`_mm256_shufflelo_epi16(x: __m256i, imm8: const int): __m256i`
==============================================================

> Shuffle 16 bit integers in the low 64 bits of 128 bit lanes of x using the control in imm8. Store the results in the low 64 bits of 128 bit lanes of destination, with the high 64 bits of 128 bit lanes being copied from x to destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_shufflelo_epi16 (__m256i x, const int imm8);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpshuflw ymm, ymm, imm8 |
| CPUID Flags | AVX2                    |

## Operation

```
dst[15:0] := (a >> (imm8[1:0] * 16))[15:0]
dst[31:16] := (a >> (imm8[3:2] * 16))[15:0]
dst[47:32] := (a >> (imm8[5:4] * 16))[15:0]
dst[63:48] := (a >> (imm8[7:6] * 16))[15:0]
dst[127:64] := a[127:64]
dst[143:128] := (a >> (imm8[1:0] * 16))[143:128]
dst[159:144] := (a >> (imm8[3:2] * 16))[143:128]
dst[175:160] := (a >> (imm8[5:4] * 16))[143:128]
dst[191:176] := (a >> (imm8[7:6] * 16))[143:128]
dst[255:192] := a[255:192]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
