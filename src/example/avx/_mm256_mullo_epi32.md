`_mm256_mullo_epi32(x: __m256i, y: __m256i): __m256i`
=====================================================

> Multiply the packed signed 32 bit integers in x and y, producing intermediate 64 bit integers, and store the low 32 bits of the intermediate integers in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mullo_epi32(__m256i x, __m256i y);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpmulld ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 7
	i := j*32
	tmp[63:0] := a[i+31:i] * b[i+31:i]
	dst[i+31:i] := tmp[31:0]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 10      | 0.66             |
| Broadwell    | 10      | 2                |
| Haswell      | 10      | 2                |
