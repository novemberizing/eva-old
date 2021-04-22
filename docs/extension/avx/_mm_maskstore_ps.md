`_mm_maskstore_ps(mem: float *, mask: __m128i, x: __m128)`
==========================================================

> Store packed single precision (32 bit) floating point elements from x into memory using mask.

## Synopsis

```c
#include <immintrin.h>

void _mm_maskstore_ps (float * mem_addr, __m128i mask, __m128 a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovps m128, xmm, xmm |
| CPUID Flags | AVX                       |

## Operation

```
FOR j := 0 to 3
	i := j*32
	IF mask[i+31]
		MEM[mem_addr+i+31:mem_addr+i] := a[i+31:i]
	FI
ENDFOR
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 1                |
