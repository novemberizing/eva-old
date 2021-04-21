`_mm256_testnzc_si256(x: __m256i, y: __m256i): __int`
=====================================================

> Compute the bitwise AND of 256 bits (representing integer data) in x and y, and set ZF to 1 if the result is zero, otherwise set ZF to 0. Compute the bitwise NOT of x and then AND with y, and set CF to 1 if the result is zero, otherwise set CF to 0. Return 1 if both the ZF and CF values are zero, otherwise return 0.

## Synopsis

```c
#include <immintrin.h>

int _mm256_testnzc_si256 (__m256i a, __m256i b);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | vptest ymm, ymm |
| CPUID Flags | AVX             |

## Operation

```
IF ((a[255:0] AND b[255:0]) == 0)
	ZF := 1
ELSE
	ZF := 0
FI
IF (((NOT a[255:0]) AND b[255:0]) == 0)
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
| Skylake      | 3       | 1                |