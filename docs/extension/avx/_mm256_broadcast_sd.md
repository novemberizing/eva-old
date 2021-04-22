`_mm256_broadcast_sd(p: double const *): __m256d`
=================================================

> Broadcast a double precision (64 bit) floating point element from memory to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_broadcast_sd(double const * p);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastsd ymm, m64 |
| CPUID Flags | AVX                   |

## Operation

```
tmp[63:0] := MEM[mem_addr+63:mem_addr]
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := tmp[63:0]
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
