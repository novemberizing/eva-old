`_mm256_permutevar8x32_epi32(x: __m256i, index: __m256i): __m256i`
==================================================================

> Shuffle 32 bit integers in a across lanes using the corresponding index in index, and store the result destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_permutevar8x32_epi32(__m256i a, __m256i index);
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vpermd ymm, ymm, ymm |
| CPUID Flags | AVX2                 |

## Operation

```
FOR j := 0 to 7
	i := j*32
	id := idx[i+2:i]*32
	dst[i+31:i] := a[id+31:id]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
