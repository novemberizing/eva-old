`_mm256_storeu_si256(mem: __m256i *, x: __m256i)`
=================================================

> Store 256 bits of integer data from x into memory. mem address does not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

void _mm256_storeu_si256 (__m256i * mem_addr, __m256i a);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovdqu m256, ymm |
| CPUID Flags | AVX               |

## Operation

```
MEM[mem_addr+255:mem_addr] := a[255:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 1                |
| Broadwell    | 1       | 0.25             |
| Haswell      | 1       | 0.25             |
| Ivy Bridge   | 1       | 0.5              |
