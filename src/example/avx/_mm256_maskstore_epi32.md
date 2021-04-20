`_mm256_maskstore_epi32(mem: int *, mask: __m256i, __m256i x)`
==============================================================

> Store packed 32 bit integers from x into memory using mask (elements are not stored when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

void _mm256_maskstore_epi32 (int* mem_addr, __m256i mask, __m256i x);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovd m256, ymm, ymm |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 7
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
| Broadwell    | -       | 2                |
| Haswell      | -       | 2                |
