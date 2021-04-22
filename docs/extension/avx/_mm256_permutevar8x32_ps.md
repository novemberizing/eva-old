`_mm256_permutevar8x32_ps(x: __m256, index: __m256i): __m256`
=============================================================

> Shuffle single precision (32 bit) floating point elements in a across lanes using the corresponding index in index.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_permutevar8x32_ps (__m256 a, __m256i idx);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpermps ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	id := idx[i+2:i]*32
	dst[i+31:i] := a[id+31:id]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
