`_mm256_sub_epi64(x: __m256i, y: __m256i)`
==========================================

> Subtract packed 64 bit integers in y from packed 64 bit integers in x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sub_epi64 (__m256i a, __m256i b);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpsubq ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[i+63:i] - b[i+63:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
