`_mm256_cvtepu8_epi16(x: __m128i): __m256i`
===========================================

> Zero extend packed unsigned 8 bit integers in x to packed 16 bit integers, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cvtepu8_epi16(__m128i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vpmovzxbw ymm, xmm |
| CPUID Flags | AVX2               |

## Operation

```
FOR j := 0 to 15
	i := j*8
	l := j*16
	dst[l+15:l] := ZeroExtend16(a[i+7:i])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |

