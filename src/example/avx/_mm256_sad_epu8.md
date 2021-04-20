`_mm256_sad_epu8(x: __m256i, y: __m256i): __m256i`
==================================================

> Compute the absolute differences of packed unsigned 8 bit integers in x and y, then horizontally sum each consecutive 8 differences to produce four unsigned 16 bit integers, and pack these unsigned 16 bit integers in the low 16 bits of 64 bit elements in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_sad_epu8 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsadbw ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 31
	i := j*8
	tmp[i+7:i] := ABS(a[i+7:i] - b[i+7:i])
ENDFOR
FOR j := 0 to 3
	i := j*64
	dst[i+15:i] := tmp[i+7:i] + tmp[i+15:i+8] + tmp[i+23:i+16] + tmp[i+31:i+24] + 
	               tmp[i+39:i+32] + tmp[i+47:i+40] + tmp[i+55:i+48] + tmp[i+63:i+56]
	dst[i+63:i+16] := 0
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 5       | 1                |
| Haswell      | 5       | 1                |
