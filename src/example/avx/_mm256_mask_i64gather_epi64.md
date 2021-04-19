`_mm256_mask_i64gather_epi64(source: __m256i, addr: int64 const *, index: __m256i, scale: const int): __m256i`
==================================================================================

> Gather 64 bit integers from memory using 64 bit indices. 64 bit elements are loaded from addresses starting at base address and offset by each 64 bit element in index (each index is scaled by the factor in scale). Gathered elements are merged into destination using mask (elements are copied from source when the highest bit is not set in the corresponding element). scale should be 1, 2, 4, or 8.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_mask_i64gather_epi64 (__m256i src, __int64 const* base_addr, __m256i vindex, __m256i mask, const int scale);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vpgatherqq ymm, vm64x, ymm |
| CPUID Flags | AVX2                       |

## Operation

```
FOR j := 0 to 3
	i := j*64
	m := j*64
	IF mask[i+63]
		addr := base_addr + vindex[m+63:m] * ZeroExtend64(scale) * 8
		dst[i+63:i] := MEM[addr+63:addr]
	ELSE
		dst[i+63:i] := src[i+63:i]
	FI
ENDFOR
mask[MAX:256] := 0
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Broadwell    | ~16     | ~5               |
| Haswell      | ~15     | ~7               |
