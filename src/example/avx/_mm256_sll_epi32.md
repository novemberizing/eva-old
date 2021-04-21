`_mm256_sll_epi32(x: __m256i, count: __m128i): __m256i`
=======================================================

> Shift packed 32 bit integers in x left by count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sll_epi32 (__m256i a, __m128i count);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpslld ymm, ymm, xmm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF count[63:0] > 31
		dst[i+31:i] := 0
	ELSE
		dst[i+31:i] := ZeroExtend32(a[i+31:i] << count[63:0])
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
