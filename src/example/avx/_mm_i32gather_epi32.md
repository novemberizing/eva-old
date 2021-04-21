`_mm_i32gather_epi32(base: int const *, index: __m128i, scale: const int)`
==========================================================================

> Gather 32 bit integer from memory using 32 bit indices. 32 bit elements are loaded from addresse starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m128i _mm_i32gather_epi32 (int const* base_addr, __m128i vindex, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vpgatherdd xmm, vm32x, xmm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 3
	i := j*32
	m := j*32
	addr := base_addr + SignExtend64(vindex[m+31:m]) * ZeroExtend64(scale) * 8
	dst[i+31:i] := MEM[addr+31:addr]
ENDFOR
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Broadwell    | ~17     | ~5               |
| Haswell      | ~14     | ~7               |

