`_mm_i64gather_ps(base: float const *, index: __m128i, scale: const int): __m128`
=================================================================================

> Gather single precision (32 bit) floating point elements from memory using 64 bit indices. 32 bit elements are loaded from addresses starting at base address and offset by each 64 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm_i64gather_ps (float const* base_addr, __m128i vindex, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vgatherqps xmm, vm64x, xmm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 1
	i := j*32
	m := j*64
	addr := base_addr + vindex[m+63:m] * ZeroExtend64(scale) * 8
	dst[i+31:i] := MEM[addr+31:addr]
ENDFOR
dst[MAX:64] := 0
```
