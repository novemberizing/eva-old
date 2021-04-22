`_mm_srlv_epi64(x: __m128i, count: __m128i): __m128i`
=====================================================

> Shift packed 64 bit integers in x right by the amount specified by the corresponding element in count while shifting in zeros, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_srlv_epi64 (__m128i a, __m128i count);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpsrlvq xmm, xmm, xmm |
| CPUID Flags | AVX2                  |

## Operation

```
FOR j := 0 to 1
	i := j*64
	IF count[i+63:i] < 64
		dst[i+63:i] := ZeroExtend64(a[i+63:i] >> count[i+63:i])
	ELSE
		dst[i+63:i] := 0
	FI
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
