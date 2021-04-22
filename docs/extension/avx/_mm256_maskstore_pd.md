`_mm256_maskstore_pd(mem: double *, mask: __m256i, x: __m256d)`
===============================================================

> Store packed double precision (64 bit) floating point elements from x into memory using mask.

## Synopsis

```c
#include <immintrin.h>

void _mm256_maskstore_pd (double * mem_addr, __m256i mask, __m256d a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovpd m256, ymm, ymm |
| CPUID Flags | AVX                       |

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
| Ivy Bridge   | -       | 2                |

