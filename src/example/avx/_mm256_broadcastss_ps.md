`_mm256_broadcastss_ps(x: __m128): __m256`
==========================================

> Broadcast the low single precision (32 bit) floating point element from x to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_broadcastss_ps(__m128 x);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastss ymm, xmm |
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
