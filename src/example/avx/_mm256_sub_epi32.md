`_mm256_sub_epi32(x: __m256i, y: __m256i)`
==========================================

> Subtract packed 32 bit integers in y from packed 32 bit integers in x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sub_epi32 (__m256i a, __m256i b);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsubd ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[i+31:i] - b[i+31:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |

