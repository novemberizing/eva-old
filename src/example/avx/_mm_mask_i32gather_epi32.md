`_mm_mask_i32gather_epi32(source: __m128i, base: int const *, index: __m128i, mask: __m128i, scale: const int): __m128i`
========================================================================================================================

> Gather 32 bit integers from memory using 32 bit indices. 32 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 3, or 8.

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

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Broadwell    | ~17     | ~5               |
| Haswell      | ~14     | ~7               |
