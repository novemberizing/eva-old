`_mm256_broadcastq_epi64(x: __m128i): __m256i`
==============================================

> Broadcast the low packed 64 bit integer from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_broadcastq_epi64(__m128i x)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpbroadcastq ymm, xmm |
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
