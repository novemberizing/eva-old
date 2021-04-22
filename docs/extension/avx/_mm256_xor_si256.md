`_mm256_xor_si256(x: __m256i, y: __m256i): __m256i`
===================================================

> Compute the bitwise XOR of 256 bits (representing integer data) in x and y, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_xor_si256 (__m256i a, __m256i b);
```

## Operation

```
dst[255:0] := (a[255:0] XOR b[255:0])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |

