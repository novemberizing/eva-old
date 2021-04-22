`_mm256_andnot_si256(x: __m256i, y: __m256i): __m256i`
======================================================

> Compute the bitwise NOT of 256 bits (representing integer data) in x and then AND with y, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_andnot_si256(__m256i x, __m256i y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpandn ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
dst[255:0] := ((NOT a[255:0]) AND b[255:0])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
