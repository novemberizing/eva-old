`_mm256_sll_epi64(x: __m256i, count: __m128i): __m256i`
=======================================================

> Shift packed 64 bit integers in x left by count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sll_epi64 (__m256i a, __m128i count);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsllq ymm, ymm, xmm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF count[63:0] > 63
		dst[i+63:i] := 0
	ELSE
		dst[i+63:i] := ZeroExtend64(a[i+63:i] << count[63:0])
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
