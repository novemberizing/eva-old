`_mm256_loadu_pd(mem: double const *): __m256d`
===============================================

> Load 256 bits (composed of 4 packed double precision (64 bit) floating point elements) from memory into destination. mem address does not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_loadu_pd (double const * mem_addr)
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovupd ymm, m256 |
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
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
| Ivy Bridge   | 1       | 1                |
