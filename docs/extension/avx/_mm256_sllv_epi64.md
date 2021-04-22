`_mm256_sllv_epi64(x: __m256i, count: __m256i): __m256i`
========================================================

> Shift packed 64 bit integers in x left by the amount specified by the corresponding element in count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sllv_epi64 (__m256i a, __m256i count);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsllvq ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF count[i+63:i] < 64
		dst[i+63:i] := ZeroExtend64(a[i+63:i] << count[i+63:i])
	ELSE
		dst[i+63:i] := 0
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
| Broadwell    | 2       | 2                |
| Haswell      | 2       | 2                |