`_mm_mask_i32gather_pd(source: __m128d, base: double const *, index: __m128i, mask: __m128d, scale: const int): __m128d`
========================================================================================================================

> Gather double precision (64 bit) floating point elements from memory using 32 bit indices. 64 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm_mask_i32gather_pd (__m128d src, double const* base_addr, __m128i vindex, __m128d mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherdpd xmm, vm32x, xmm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 1
	i := j*64
	m := j*32
	IF mask[i+63]
		addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
		dst[i+63:i] := MEM[addr+63:addr]
	ELSE
		dst[i+63:i] := src[i+63:i]
	FI
ENDFOR
mask[MAX:128] := 0
dst[MAX:128] := 0
```

