`_mm_srlv_epi32(x: __m128i, count: __m128i): __m128i`
=====================================================

> Shift packed 32 bit integers in x right by the amount specified by the corresponding element in count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_srlv_epi32 (__m128i a, __m128i count);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsrlvd xmm, xmm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 3
	i := j*32
	IF count[i+31:i] < 32
		dst[i+31:i] := ZeroExtend32(a[i+31:i] >> count[i+31:i])
	ELSE
		dst[i+31:i] := 0
	FI
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
