`_mm256_cvtsd_f64(x: __m256d): double`
======================================

> Copy the lower double precision (64 bit) floating point element of x to destination.

## Synopsis

```c
#include <immintrin.h>

double _mm256_cvtsd_f64(__m256d x);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vmovsd m64, xmm |
| CPUID Flags | AVX             |

## Operation

```
dst[63:0] := a[63:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 1                |
