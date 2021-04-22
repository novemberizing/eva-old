`_mm_testnzc_pd(x: __m128d, y: __m128d): __m128d`
=================================================

> Compute the bitwise AND of 128 bits (representing double precision (64 bit) floating point elements) in x and y, producing an intermediate 128 bit value, and set ZF to 1 if the sign bit of each 64 bit element in the intermediate value is zero, otherwise set ZF to 0. Compute the bitwise NOT of x and then AND with y, producing an intermediate value, and set CF to 1 if the sign bit of each 64 bit element in theintermediate value is zero, otherwise set CF to 0. Return 1 if both the ZF and CF values are zero, otherwise return 0.

## Synopsis

```c
#include <immintrin.h>

int _mm_testnzc_pd (__m128d a, __m128d b);
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
IF (ZF == 0 && CF == 0)
	dst := 1
ELSE
	dst := 0
FI
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 2       | 1                |
