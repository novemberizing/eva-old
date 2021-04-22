`_mm256_broadcastsd_pd(x: __m128d): __m256d`
============================================

> Broadcast the low double precision (64 bit) floating point element from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_broadcastsd_pd(__m128d x);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastsd ymm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[63:0]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |

