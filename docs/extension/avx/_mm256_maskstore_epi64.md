`_mm256_maskstore_epi64(mem: int64 *, mask: __m256i, y: __m256i)`
=================================================================

> Store packed 64 bit integers from x into memory using mask (elements are not stored when the highest bit is not set in the corresponding element).

## Synopsis

```c
#include <immintrin.h>

void _mm256_maskstore_epi64 (__int64* mem_addr, __m256i mask, __m256i a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovq m256, ymm, ymm |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 3
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
| Broadwell    | -       | 2                |
| Haswell      | -       | 2                |
