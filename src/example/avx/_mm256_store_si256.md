`_mm256_store_si256(mem: __m256i, x: __m256i)`
==============================================

> Store 256 bits of integer data from x into memory. mem address must be aligned 32 byte boundary or a general protection exception may be generated.

## Synopsis

```c
#include <immintrin.h>

void _mm256_store_si256 (__m256i * mem_addr, __m256i a);
```

| -           | Description       |
| ----------- | ----------------- |
| Instruction | vmovdqa m256, ymm |
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
