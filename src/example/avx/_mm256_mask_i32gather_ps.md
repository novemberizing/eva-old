`_mm256_mask_i32gather_ps(source: __m256, base: const float *, index: __m256i, mask: __m256, scale: const int): __m256`
==============================================================================

> Gather single precision (32 bit) floating point elements from memory using 32 bit indices. 32 bit elements are loaded from addresses starting at base and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_mask_i32gather_ps(__m256 src, float const* base_addr, __m256i vindex, __m256 mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherdps ymm, vm32x, ymm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 7
	i := j*32
	m := j*32
	IF mask[i+31]
		addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
		dst[i+31:i] := MEM[addr+31:addr]
	ELSE
		dst[i+31:i] := src[i+31:i]
	FI
ENDFOR
mask[MAX:256] := 0
dst[MAX:256] := 0
```

