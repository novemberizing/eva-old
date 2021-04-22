`_mm_maskstore_epi64(mem: __int64 *, mask: __m128i, x: __m128i)`
================================================================

> Store packed 64 bit integers from x into memory using mask (elements are not stored when the highest bit is not set in the correponding element).

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vpmaskmovq m128, xmm, xmm |
| CPUID Flags | AVX2                      |

## Operation

```
FOR j := 0 to 1
	i := j*64
	IF mask[i+63]
		MEM[mem_addr+i+63:mem_addr+i] := a[i+63:i]
	FI
ENDFOR
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 1                |
