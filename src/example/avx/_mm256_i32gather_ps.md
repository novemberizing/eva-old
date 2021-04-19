`_mm256_i32gather_ps(base: const float *, index: __m256i, scale: int): __m256`
==============================================================================

> Gather single precision (32 bit) floating point elements from memory using 32 bit indices. 32 bit elements are loaded from addresses at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_i32gather_ps(float const* base, __m256i vindex, const int scale);
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
	addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
	dst[i+31:i] := MEM[addr+31:addr]
ENDFOR
dst[MAX:256] := 0
```

