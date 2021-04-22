`_mm256_lddqu_si256(mem: __m256i const *): __m256i`
===================================================

> Load 256 bits of integer data from unaligned memory into destination. This intrinsic may perform better than _mm256_loadu_si256 when data crosses a cache line boundary.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_lddqu_si256 (__m256i const * mem_addr);
```

| -           | Description      |
| ----------- | ---------------- |
| Instruction | vlddqu ymm, m256 |
| CPUID Flags | AVX              |

## Operation

```
dst[255:0] := MEM[mem_addr+255:mem_addr]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
