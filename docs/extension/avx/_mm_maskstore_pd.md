`_mm_maskstore_pd(mem: double *, mask: __m128i, x: __m128d)`
============================================================

> Store packed double precision (64 bit) floating point elements from x into memory using mask.

## Synopsis

```c
#include <immintrin.h>

void _mm_maskstore_pd (double * mem_addr, __m128i mask, __m128d a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovpd m128, xmm, xmm |
| CPUID Flags | AVX                       |

## Operation

```
FOR j := 0 to 1
	i := j*64
	IF mask[i+63]
		MEM[mem_addr+i+63:mem_addr+i] := a[i+63:i]
	FI
ENDFOR
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 1                |
