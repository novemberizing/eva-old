`_mm_maskload_ps(mem: float const *, mask: __m128i): __m128`
============================================================

> Load packed single precision (32 bit) floating point elements from memory into destination using mask (elements are zeroed out when the high bit of the corresponding element is not set).

## Synopsis

```c
#include <immintrin.h>

__m128 _mm_maskload_ps (float const * mem_addr, __m128i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovps xmm, xmm, m128 |
| CPUID Flags | AVX                       |

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