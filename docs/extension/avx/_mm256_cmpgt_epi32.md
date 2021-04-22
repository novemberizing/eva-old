`_mm256_cmpgt_epi32(x: __m256i, y: __m256i): __m256i`
=====================================================

> Compute packed signed 32 bit integers in x and y for greater than, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cmpgt_epi32(__m256i x, __m256i y);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpcmpgtd ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := ( a[i+31:i] > b[i+31:i] ) ? 0xFFFFFFFF : 0
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
