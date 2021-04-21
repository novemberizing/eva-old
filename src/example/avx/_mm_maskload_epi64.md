`_mm_maskload_epi64(mem: __int64 const *, mask: __m128i): __m128i`
==================================================================

> Load packed 64 bit integers from memory into destination using mask (elements are zeroed out when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_maskload_epi64 (__int64 const* mem_addr, __m128i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovq xmm, xmm, m128 |
| CPUID Flags | AVX2                      |

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
