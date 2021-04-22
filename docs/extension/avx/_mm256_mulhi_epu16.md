`_mm256_mulhi_epu16(x: __m256i, y: __m256i): __m256i`
=====================================================

> Multiply the packed unsigned 16 bit integers in x and y, producing intermediate 32 bit integers, and store the high 16 bits of the intermediate integers in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mulhi_epu16(__m256i a, __m256i b);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vpmulhuw ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
FOR j := 0 to 15
	i := j*16
	tmp[31:0] := a[i+15:i] * b[i+15:i]
	dst[i+15:i] := tmp[31:16]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 0.5              |
| Skylake      | 5       | 0.5              |
