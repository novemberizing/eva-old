`_mm256_storeu_pd(mem: double *, x: __m256d)`
=============================================

> Store 256 bits (composed of 4 packed double precision (64 bit) floating point elements) from x into memory. mem address does not need to be aligned on any particular boundary.

## Synopsis

```c
#include <immintrin.h>

void _mm256_storeu_pd (double * mem_addr, __m256d a);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovupd m256, ymm |
| CPUID Flags | AVX               |

## Operation

```
MEM[mem_addr+255:mem_addr] := a[255:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 1                |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
| Ivy Bridge   | 1       | 1                |
