`_mm256_slli_epi32(x: __m256i, imm8: int): __m256i`
===================================================

> Shift packed 32 bit integers in x left by imm8 while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_slli_epi32 (__m256i a, int imm8);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpslld ymm, ymm, imm8 |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF imm8[7:0] > 31
		dst[i+31:i] := 0
	ELSE
		dst[i+31:i] := ZeroExtend32(a[i+31:i] << imm8[7:0])
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
