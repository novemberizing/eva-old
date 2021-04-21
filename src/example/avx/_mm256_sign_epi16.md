`_mm256_sign_epi16(x: __m256i, y: __m256i): __m256i`
====================================================

> Negate packed signed 16 bit integers in x when the corresponding signed 16 bit integer in y is negative, and store the results in destination. Element in destination are zeroed out when the corresponding element in y is zero.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sign_epi16 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsignw ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 15
	i := j*16
	IF b[i+15:i] < 0
		dst[i+15:i] := -(a[i+15:i])
	ELSE IF b[i+15:i] == 0
		dst[i+15:i] := 0
	ELSE
		dst[i+15:i] := a[i+15:i]
	FI
ENDFOR
dst[MAX:256] := 0
```
