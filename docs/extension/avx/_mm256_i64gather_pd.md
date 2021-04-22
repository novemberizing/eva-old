`_mm256_i64gather_pd(addr: double const *, index: __m256i, scale: const int): __m256d`
==============================================================================

> Gather double precision (64 bit) floating point elements from memory using 64 bit elements are loaded from addresses starting at base address and offset by each 64 bit element in vindex (each index is scaled by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_i64gather_pd (double const* base_addr, __m256i vindex, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherqpd ymm, vm64x, ymm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 3
	i := j*64
	m := j*64
	addr := base_addr + vindex[m+63:m] * ZeroExtend64(scale) * 8
	dst[i+63:i] := MEM[addr+63:addr]
ENDFOR
dst[MAX:256] := 0
```
