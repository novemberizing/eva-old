`_mm256_maddubs_epi16(x: __m256i, y: __m256i): __m256i`
=======================================================

> Vertically multiply each unsigned 8 bit integer from x with the corresponding signed 8 bit integer from y, producing intermediate signed 16 bit integers. Horizontally add adjacent pairs of intermediate signed 16 bit integers, and pack the saturated results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_maddubs_epi16 (__m256i a, __m256i b);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpmaddubsw ymm, ymm, ymm |
| CPUID Flags | AVX2                     |

## Operation

```
FOR j := 0 to 15
	i := j*16
	dst[i+15:i] := Saturate16( a[i+15:i+8]*b[i+15:i+8] + a[i+7:i]*b[i+7:i] )
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 0.5              |
| Broadwell    | 5       | 1                |
| Haswell      | 5       | 1                |
