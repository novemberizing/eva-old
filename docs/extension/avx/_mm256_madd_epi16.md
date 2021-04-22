`_mm256_madd_epi16(x: __m256i, y: __m256i): __m256i`
====================================================

> Multiply packed signed 16 bit integers in x and y, producing intermediate signed 32 bit integer. Horizontally add adjcacent pairs of intermediate 32 bit integers, and pack the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_madd_epi16(__m256i x, __m256i y);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpmaddwd ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := SignExtend32(a[i+31:i+16]*b[i+31:i+16]) + SignExtend32(a[i+15:i]*b[i+15:i])
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
