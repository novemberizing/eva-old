`_mm256_mulhrs_epi16(x: __m256i, y: __m256i): __m256i`
======================================================

> Multiply packed signed 16 bit integers in x and y, producing intermediate signed 32 bit integers. Truncate each intermediate integer to the 18 most significant bits, round by adding 1, and store bits [16:1] to destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mulhrs_epi16 (__m256i x, __m256i y);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpmulhrsw ymm, ymm, ymm |
| CPUID Flags | AVX2                    |

## Operation

```
FOR j := 0 to 15
	i := j*16
	tmp[31:0] := ((SignExtend32(a[i+15:i]) * SignExtend32(b[i+15:i])) >> 14) + 1
	dst[i+15:i] := tmp[16:1]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 0.5              |
| Skylake      | 5       | 0.5              |
| Broadwell    | 5       | 1                |
| Haswell      | 5       | 1                |
