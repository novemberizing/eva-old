`_mm_maskload_epi32(mem: int const *, mask: __m128i): __m128i`
==============================================================

> Load packed 32 bit integers from memory into destination using mask (elements are zeroed out when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_maskload_epi32 (int const* mem_addr, __m128i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovd xmm, xmm, m128 |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 3
	i := j*32
	IF mask[i+31]
		dst[i+31:i] := MEM[mem_addr+i+31:mem_addr+i]
	ELSE
		dst[i+31:i] := 0
	FI
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
