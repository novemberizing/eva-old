`_mm256_cvtepi8_epi32(x: __m128i): __m256i`
===========================================

> Sign extend packed 8 bit integers in x to packed 32 bit integers, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cvtepi8_epi32(__m128i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vpmovsxbd ymm, xmm |
| CPUID Flags | AVX2               |

## Operation

```
FOR j := 0 to 7
	i := 32*j
	k := 8*j
	dst[i+31:i] := SignExtend32(a[k+7:k])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |