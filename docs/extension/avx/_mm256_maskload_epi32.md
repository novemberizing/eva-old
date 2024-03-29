`_mm256_maskload_epi32(mem: int const *, mask: __m256i): __m256i`
=================================================================

> Load packed 32 bit integers from memory into destination using mask (elements are zeroed out when the highest bit is not set in the correspoding element).

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_maskload_epi32 (int const* mem_addr, __m256i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovd ymm, ymm, m256 |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 7
	i := j*32
	IF mask[i+31]
		dst[i+31:i] := MEM[mem_addr+i+31:mem_addr+i]
	ELSE
		dst[i+31:i] := 0
	FI
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 8       | 0.5              |
| Skylake      | 8       | 0.5              |
| Broadwell    | 8       | 2                |
| Haswell      | 8       | 2                |
