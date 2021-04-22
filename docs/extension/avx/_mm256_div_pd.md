`_mm256_div_pd(x: __m256d, y: __m256d): __m256d`
================================================

> Divide packed double precision (64 bit) floating point elements in x by packed elemtns in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_div_pd(__m256d x, __m256d y);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vdivpd ymm, ymm, ymm |
| CPUID Flags | AVX                  |

## Operation

```
FOR j := 0 to 3
	i := 64*j
	dst[i+63:i] := a[i+63:i] / b[i+63:i]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture    | Latency | Throughput (CPI) |
| --------------- | ------- | ---------------- |
| Icelake         | -       | 8                |
| Skylake         | 14      | 8                |
| Knights Landing | 38      | ~10              |
| Broadwell       | 16-23   | 16               |
| Haswell         | 25-35   | 27               |
| Ivy Bridge      | 27-35   | 28               |
