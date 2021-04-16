`_mm256_cvtss_f32(x: __m256): float`
====================================

> Copy the lower single precision (32 bit) floating point element of x to destination.

## Synopsis

```c
#include <immintrin.h>

float _mm256_cvtss_f32(__m256 a);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vmovss m32, xmm |
| CPUID Flags | AVX             |

## Operation

```
dst[31:0] := a[31:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 1                |
