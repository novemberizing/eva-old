`_mm256_div_ps(x: __m256, y: __m256): __m256`
=============================================

> Divide packed single precision (32 bit) floating point elements in x by packed elements in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_div_ps(__m256 x, __m256 y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vdivps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 7
	i := 32*j
	dst[i+31:i] := a[i+31:i] / b[i+31:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture    | Latency | Throughput (CPI) |
| --------------- | ------- | ---------------- |
| Icelake         | 11      | 5                |
| Skylake         | 11      | 5                |
| Knights Landing | 38      | ~10              |
| Broadwell       | 13-17   | 10               |
| Haswell         | 17-21   | 13               |
| Ivy Bridge      | 18-21   | 14               |
