`_mm256_hsub_ps(x: __m256, y: __m256): __m256`
==============================================

> Horizontally add adjacent pairs of single precision (32 bit) floating point elements in x and y, and pack the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_hsub_ps(__m256 x, __m256 y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vhsubps ymm, ymm, ymm |
| CPUID Flags | AVX                   |

## Operation

```
dst[31:0] := a[31:0] - a[63:32]
dst[63:32] := a[95:64] - a[127:96]
dst[95:64] := b[31:0] - b[63:32]
dst[127:96] := b[95:64] - b[127:96]
dst[159:128] := a[159:128] - a[191:160]
dst[191:160] := a[223:192] - a[255:224]
dst[223:192] := b[159:128] - b[191:160]
dst[255:224] := b[223:192] - b[255:224]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 2                |
