`_mm_i32gather_epi64(base: __int64 const *, index: __m128i, scale: const int): __m128i`
=======================================================================================

> Gather 64 bit integers from memory using 32 bit indices. 64 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_i32gather_epi64 (__int64 const* base_addr, __m128i vindex, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vpgatherdq xmm, vm32x, xmm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 1
	i := j*64
	m := j*32
	addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
	dst[i+63:i] := MEM[addr+63:addr]
ENDFOR
dst[MAX:128] := 0
```
