`_mm_maskstore_epi32(mem: int *, mask: __m128i, x: __m128i)`
============================================================

> Store packed 32 bit integers from x into memory using mask (elements are not stored when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

void _mm_maskstore_epi32 (int* mem_addr, __m128i mask, __m128i a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovd m128, xmm, xmm |
| CPUID Flags | AVX2                      |

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