`_mm256_loadu_si256(mem: __m256i const *): __m256i`
===================================================

> Load 256 bits of integer data from memory into destination. mem address does not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_loadu_si256 (__m256i const * mem_addr);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovdqu ymm, m256 |
| CPUID Flags | AVX               |

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
| Broadwell    | 1       | 0.25             |
| Haswell      | 1       | 0.25             |
| Ivy Bridge   | 1       | 0.5              |
