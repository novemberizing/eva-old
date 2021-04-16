`_mm256_cvtepi8_epi64(x: __m128i): __m256i`
===========================================

> Sign extend packed 8 bit integers in the low 8 bytes of x to packed 64 bit integers, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cvtepi8_epi64(__m128i x);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vpmovsxbq ymm, xmm |
| CPUID Flags | AVX2               |

## Operation

```
FOR j := 0 to 3
	i := 64*j
	k := 8*j
	dst[i+63:i] := SignExtend64(a[k+7:k])
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |