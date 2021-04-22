`_mm256_srli_epi64(x: __m256i, imm8: int): __m256i`
===================================================

> Shift packed 64 bit integers in x right by imm8 while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_srli_epi64 (__m256i a, int imm8);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsrlq ymm, ymm, imm8 |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF imm8[7:0] > 63
		dst[i+63:i] := 0
	ELSE
		dst[i+63:i] := ZeroExtend64(a[i+63:i] >> imm8[7:0])
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
