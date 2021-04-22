`_mm256_mask_i32gather_epi64(source: __m256i, base: int64 const *, index: __m128i, mask: __m256i, scale: const int): __m256i`
========================================================================================

> Gather 64-bit integers from memory using 32-bit indices. 64-bit elements are loaded from addresses starting at base_addr and offset by each 32-bit element in vindex (each index is scaled by the factor in scale). Gathered elements are merged into dst using mask (elements are copied from src when the highest bit is not set in the corresponding element). scale should be 1, 2, 4 or 8.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mask_i32gather_epi64(__m256i source, __int64 const* base, __m128i index, __m256i mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vpgatherdq ymm, vm32x, ymm |
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

