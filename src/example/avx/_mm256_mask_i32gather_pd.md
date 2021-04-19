`_mm256_mask_i32gather_pd(source: __m256d, base: const double *, index: __m128i, mask: __m256d, scale: const int): __m256d`
================================================================================

> Gather double precision (64 bit) floating point elements from memory using 32 bit indices. 64 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). Scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_mask_i32gather_pd(__m256d src, double const* base_addr, __m128i vindex, __m256d mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherdpd ymm, vm32x, ymm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 3
	i := j*64
	m := j*32
	IF mask[i+63]
		addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
		dst[i+63:i] := MEM[addr+63:addr]
	ELSE
		dst[i+63:i] := src[i+63:i]
	FI
ENDFOR
mask[MAX:256] := 0
dst[MAX:256] := 0
```
