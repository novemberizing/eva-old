`_mm256_mask_i32gather_epi32(source: __m256i, base: int const *, index: __m256i, mask: __m256i, scale: const int): __m256i`
======================================================================================

> Gather 32 bit integers from memory using 32 bit indices. 32 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

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

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Broadwell    | ~19     | ~6               |
| Haswell      | ~20     | ~10              |
