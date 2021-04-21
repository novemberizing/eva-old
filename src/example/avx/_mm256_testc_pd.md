`_mm256_testc_pd(x: __m256d, y: __m256d): int`
==============================================

> Compute the bitwise AND of 256 bits (representing double precision (64 bit) floating point elements) in x and y, producing an intermediate 256 bit value, and set ZF to 1 if the sign bit of each 64 bit element in the intermediate value is zero, otherwise set ZF to 0. Compute the bitwise NOT of x and then ADN with y, producing an intermediate value, and set CF to 1 if the sign bit of each 64 bit element in the intermediate value is zero, otherwise set CF to 0. Return the CF value.

## Synopsis

```c
#include <immintrin.h>

int _mm256_testc_pd (__m256d a, __m256d b);
```

| -           | Description      |
| ----------- | ---------------- |
| Instruction | vtestpd ymm, ymm |
| CPUID Flags | AVX              |

## Operation

```
tmp[255:0] := a[255:0] AND b[255:0]
IF (tmp[63] == 0 && tmp[127] == 0 && tmp[191] == 0 && tmp[255] == 0)
	ZF := 1
ELSE
	ZF := 0
FI
tmp[255:0] := (NOT a[255:0]) AND b[255:0]
IF (tmp[63] == 0 && tmp[127] == 0 && tmp[191] == 0 && tmp[255] == 0)
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
