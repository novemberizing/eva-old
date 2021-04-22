`_mm256_sll_epi16(x: __m256i, y: __m256i): __m256i`
===================================================

> Shift packed 16 bit integers in x left by count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sll_epi16 (__m256i a, __m128i count);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsllw ymm, ymm, xmm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 15
	i := j*16
	IF count[63:0] > 15
		dst[i+15:i] := 0
	ELSE
		dst[i+15:i] := ZeroExtend16(a[i+15:i] << count[63:0])
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 4       | 1                |
| Broadwell    | 4       | 1                |
| Haswell      | 4       | 1                |
