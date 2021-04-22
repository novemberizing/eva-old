`_mm256_broadcast_ss(p: float const *): __m256`
===============================================

> Broadcast a single precision (32 bit) floating point element from memory to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_broadcast_ss (float const * p);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastss ymm, m32 |
| CPUID Flags | AVX                   |

## Operation

```
tmp[31:0] := MEM[mem_addr+31:mem_addr]
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := tmp[31:0]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
