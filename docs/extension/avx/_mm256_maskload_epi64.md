`_mm256_maskload_epi64(mem: int64 const *, mask: __m256i): __m256i`
===================================================================

> Load packed 64 bit integers from memory into destination using mask (elements are zeroed out when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_maskload_epi64 (__int64 const* mem_addr, __m256i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovq ymm, ymm, m256 |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 3
	i := j*64
	IF mask[i+63]
		dst[i+63:i] := MEM[mem_addr+i+63:mem_addr+i]
	ELSE
		dst[i+63:i] := 0
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
