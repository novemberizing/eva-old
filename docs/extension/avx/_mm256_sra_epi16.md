`_mm256_sra_epi16(x: __m256i, count: __m128i): __m256i`
=======================================================

> Shift packed 16 bit integers in x right by count while shifting in sign bits, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sra_epi16 (__m256i a, __m128i count);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsraw ymm, ymm, xmm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 15
	i := j*16
	IF count[63:0] > 15
		dst[i+15:i] := (a[i+15] ? 0xFFFF : 0x0)
	ELSE
		dst[i+15:i] := SignExtend16(a[i+15:i] >> count[63:0])
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 4       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
