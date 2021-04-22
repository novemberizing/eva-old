`_mm_maskload_pd(mem: double const *, mask: __m128i): __m128d`
==============================================================

> Load packed double precision (64 bit) floating point elements from memory into destinatino using mask (elements are zeroed out when the high bit of the corresponding element is not set).

## Synopsis

```c
#include <immintrin.h>

__m128d _mm_maskload_pd (double const * mem_addr, __m128i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovpd xmm, xmm, m128 |
| CPUID Flags | AVX                       |

## Operation

```
FOR j := 0 to 1
	i := j*64
	IF mask[i+63]
		dst[i+63:i] := MEM[mem_addr+i+63:mem_addr+i]
	ELSE
		dst[i+63:i] := 0
	FI
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
