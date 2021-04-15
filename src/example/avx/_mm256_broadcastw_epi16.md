`_mm256_broadcastw_epi16(x: __m128i): __m256i`
==============================================

> Broadcast the low packed 16 bit integer from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_broadcastw_epi16(__m128i x);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpbroadcastw ymm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 15
	i := j*16
	dst[i+15:i] := a[15:0]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
