`_mm256_cvtsi256_si32(x: __m256i): int`
=======================================

__no method__

> Copy the lower 32 bit integer in x to destination.

## Synopsis

```c
#include <immintrin.h>

int _mm256_cvtsi256_si32(__m256i x);
```

| -           | Description    |
| ----------- | -------------- |
| Instruction | vmovd r32, xmm |
| CPUID Flags | AVX            |

## Operation

```
dst[31:0] := a[31:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 2       | 1                |
