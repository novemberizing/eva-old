`_mm256_movemask_epi8(x: __m256i): int`
=======================================

> Create mask from the most significant bit of each 8 bit element in x, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

int _mm256_movemask_epi8 (__m256i a);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vpmovmskb r32, ymm |
| CPUID Flags | AVX2               |

## Operation

```
FOR j := 0 to 31
	i := j*8
	dst[j] := a[i+7]
ENDFOR
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 2       | 1                |
