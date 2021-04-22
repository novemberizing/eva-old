`_mm256_moveldup_ps(x: __m256): __m256`
=======================================

> Duplicate even indexed single precision (32 bit) floating point elements from x, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_moveldup_ps (__m256 a);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vmovsldup ymm, ymm |
| CPUID Flags | AVX                |

## Operation

```
dst[31:0] := a[31:0] 
dst[63:32] := a[31:0] 
dst[95:64] := a[95:64] 
dst[127:96] := a[95:64]
dst[159:128] := a[159:128] 
dst[191:160] := a[159:128] 
dst[223:192] := a[223:192] 
dst[255:224] := a[223:192]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
