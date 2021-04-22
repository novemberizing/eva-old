`_mm256_mask_i64gather_epi32(source: __m128i, base: int const *, index: __m256i, mask: __m128i, scale: const int): __m128i`
================================================================================

> Gather 32 bit integers from memory using 64 bit indices. 32 bit elements are loaded from addresses starting at base address and offet by each 64 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

## Operation

```
FOR j := 0 to 3
	i := j*32
	m := j*64
	IF mask[i+31]
		addr := base_addr + vindex[m+63:m] * ZeroExtend64(scale) * 8
		dst[i+31:i] := MEM[addr+31:addr]
	ELSE
		dst[i+31:i] := src[i+31:i]
	FI
ENDFOR
mask[MAX:128] := 0
dst[MAX:128] := 0
```

