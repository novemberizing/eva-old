`_mm256_cvtepu32_epi64(x: __m128i): __m256i`
============================================

> Zero extend packed unsigned 32 bit integers in x to packed 64 bit integers, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cvtepu32_epi64(__m128i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vpmovzxdq ymm, xmm |
| CPUID Flags | AVX2               |

## Operation

```
FOR j:= 0 to 3
	i := 64*j
	k := 32*j
	dst[i+63:i] := ZeroExtend64(a[k+31:k])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |

