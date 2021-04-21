`_mm256_store_ps(mem: float*, x: __m256)`
=========================================

> Store 256 bits (composed of 8 packed single precision (32 bit) floating point elements) from x into memory. mem address must be aligned on a 32 byte boundary or a general protection exception may be generated.

## Synopsis

```c
#include <immintrin.h>

void _mm256_store_ps (float * mem_addr, __m256 a);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovaps m256, ymm |
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
