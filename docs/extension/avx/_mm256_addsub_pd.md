`_mm256_addsub_pd(x: __m256i, y: __m256i): __m256i`
===================================================

__alternatively add and subtract__

> Alternatively add and subtract packed double precision (64 bit) floating point elements in x to/from packed elements in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_addsub_pd(__m256d x, __m256d y);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vaddsubpd ymm, ymm, ymm |
| CPUID Flags | AVX                     |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF ((j & 1) == 0)
		dst[i+63:i] := a[i+63:i] - b[i+63:i]
	ELSE
		dst[i+63:i] := a[i+63:i] + b[i+63:i]
	FI
ENDFOR
dst[MAX:256] := 0
```