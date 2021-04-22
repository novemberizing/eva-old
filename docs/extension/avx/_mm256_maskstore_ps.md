`_mm256_maskstore_ps(mem: float *, mask: __m256i, y: __m256)`
=============================================================

> Store packed single precision (32 bit) floating point elements from x into memory using mask.

## Synopsis

```c
#include <immintrin.h>

void _mm256_maskstore_ps (float * mem_addr, __m256i mask, __m256 a);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovps m256, ymm, ymm |
| CPUID Flags | AVX                       |

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
| Ivy Bridge   | -       | 2                |
