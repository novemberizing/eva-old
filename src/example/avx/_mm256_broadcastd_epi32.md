`_mm256_broadcastd_epi32(x: __m128i): __m256i`
==============================================

> Broadcast the low packed 32 bit integer from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_broadcastd_epi32(__m128i x);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpbroadcastd ymm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[31:0]
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
