`_mm256_stream_pd(mem: double *, x: __m256d)`
=============================================

> Store 256 bits (composed of 4 packed double precision (64 bit) floating point elements) from x into memory using a non-temporal memory hint. mem address must be aligned on a 32 byte boundary or a general protection exception may be generated.

## Synopsis

```c
#include <immintrin.h>

void _mm256_stream_pd (double * mem_addr, __m256d a);
```

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vmovntpd m256, ymm |
| CPUID Flags | AVX                |

## Operation

```
MEM[mem_addr+255:mem_addr] := a[255:0]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 5       | 1                |
| Broadwell    | -       | 1                |
| Haswell      | -       | 1                |
| Ivy Bridge   | -       | 1                |
