`_mm256_cmpgt_epi64(x: __m256i, y: __m256i): __m256i`
=====================================================

> Compare packed signed 64 bit integers in x and y for greater than, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cmpgt_epi64(__m256i x, __m256i y);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpcmpgtq ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := ( a[i+63:i] > b[i+63:i] ) ? 0xFFFFFFFFFFFFFFFF : 0
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 5       | 1                |
| Haswell      | 5       | 1                |

