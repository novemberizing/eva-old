`_mm256_broadcastb_epi8(a: __m128i): __m256i`
=============================================

> Broadcast the low packed 8 bit integer from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_broadcastb_epi8 (__m128i x);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpbroadcastb ymm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := a[7:0]
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
