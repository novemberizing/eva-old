`_mm256_loadu_ps(mem: float const *): __m256`
=============================================

> Load 256 bits (composed of 8 packed single precision (32 bit) floating point elements) from memory into destination. mem address doest not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_loadu_ps (float const * mem_addr)
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovups ymm, m256 |
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
