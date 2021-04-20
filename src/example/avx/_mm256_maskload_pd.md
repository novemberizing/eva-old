`_mm256_maskload_pd(mem: double const *, mask: __m256i): __m256d`
=================================================================

> Load packed double precision (64 bit) floating point elements from memory into destination using mask (elements are zeroed out when the high bit of the corresponding element is not set).

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_maskload_pd (double const * mem_addr, __m256i mask);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vmaskmovpd ymm, ymm, m256 |
| CPUID Flags | AVX                       |

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
| Broadwell    | -       | 2                |
| Haswell      | -       | 2                |
| Ivy Bridge   | -       | 2                |
