`_mm256_broadcast_ps(p: __m128 const *): __m256`
================================================

> Broadcast 128 bits from memory (composed of 4 packed single precision (32 bit) floating point elements) to all elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_broadcast_ps(__m128 const * p);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vbroadcastf128 ymm, m128 |
| CPUID Flags | AVX                      |

## Operation

```
tmp[127:0] := MEM[mem_addr+127:mem_addr]
dst[127:0] := tmp[127:0]
dst[255:128] := tmp[127:0]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |
