`_mm256_mul_epi32(x: __m256i, y: __m256i): __m256i`
===================================================

> Multiply the low signed 32 bit integers from each packed 64 bit element in x and y, and store the signed 64 bit results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mul_epi32 (__m256i a, __m256i b);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpmuldq ymm, ymm, ymm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := SignExtend64(a[i+31:i]) * SignExtend64(b[i+31:i])
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
