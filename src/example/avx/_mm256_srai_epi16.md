`_mm256_srai_epi16(x: __m256i, imm8: int): __m256i`
===================================================

> Shift packed 16 bit integers in x right by imm8 while shifting in sign bits, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_srai_epi16 (__m256i a, int imm8);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsraw ymm, ymm, imm8 |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 15
	i := j*16
	IF imm8[7:0] > 15
		dst[i+15:i] := (a[i+15] ? 0xFFFF : 0x0)
	ELSE
		dst[i+15:i] := SignExtend16(a[i+15:i] >> imm8[7:0])
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
