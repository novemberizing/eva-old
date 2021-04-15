`_mm256_broadcastsi128_si256(a: __m128i): __m256i`
==================================================

> Broadcast 128 bits of integer data from x to all 128 bit lanes in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_broadcastsi128_si256(__m128i x);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vbroadcasti128 ymm, m128 |
| CPUID Flags | AVX2                     |

## Operation

```
dst[127:0] := a[127:0]
dst[255:128] := a[127:0]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
