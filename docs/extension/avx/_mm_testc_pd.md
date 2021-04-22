`_mm_testc_pd(x: __m128d, y: __m128d): int`
===========================================

> Compute the bitwise AND of 128 bits (representing double precision (64 bit) floating point elements) in x and y, producing an intermediate 128 bit value, and set ZF to 1 if the sign bit of each 64 bit element in the intermediate value is zero, otherwise set ZF to 0. Compute the bitwise NOT of x and then AND with y, producing an intermediate value, and set CF to 1 if the sign bit of each 64 bit element in the intermediate value is zero, otherwise set CF to 0. Return the CF value.

## Synopsis

```c
#include <immintrin.h>

int _mm_testc_pd (__m128d a, __m128d b);
```

| -           | Description      |
| ----------- | ---------------- |
| Instruction | vtestpd xmm, xmm |
| CPUID Flags | AVX              |

## Operation

```
tmp[127:0] := a[127:0] AND b[127:0]
IF (tmp[63] == 0 && tmp[127] == 0)
	ZF := 1
ELSE
	ZF := 0
FI
tmp[127:0] := (NOT a[127:0]) AND b[127:0]
IF (tmp[63] == 0 && tmp[127] == 0)
	CF := 1
ELSE
	CF := 0
FI
dst := CF
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 2       | 1                |
