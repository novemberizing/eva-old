`_mm_mask_i32gather_ps(source: __m128, base: float const *, index: __m128i, mask: __m128, scale: const int): __m128`
====================================================================================================================

> Gather single precision (32 bit) floating point elements from memory using 32 bit indices. 32 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm_mask_i32gather_ps (__m128 src, float const* base_addr, __m128i vindex, __m128 mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherdps xmm, vm32x, xmm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 3
	i := j*32
	m := j*32
	IF mask[i+31]
		addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
		dst[i+31:i] := MEM[addr+31:addr]
	ELSE
		dst[i+31:i] := src[i+31:i]
	FI
ENDFOR
mask[MAX:128] := 0
dst[MAX:128] := 0
```

