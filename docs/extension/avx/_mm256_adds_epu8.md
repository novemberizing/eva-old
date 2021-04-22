`_mm256_adds_epu8(x: __m256i, y: __m256i): __m256i`
===================================================

> Add packed unsigned 8 bit integers in x and y using saturation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_adds_epu8(__m256i x, __m256i y);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpaddusb ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[i+7:i] := SaturateU8( a[i+7:i] + b[i+7:i] )
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
