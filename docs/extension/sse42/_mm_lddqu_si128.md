`_mm_lddqu_si128(mem: __m128i const *): __m128i`
================================================

> Load 128 bits of integer data from unaligned memory into destination. This intrinsic may perform betten than `_mm_loadu_si128` when the data crosses a cache line boundary.

## Synopsis

```c
#include <pmmintrin.h>

__m128i _mm_lddqu_si128 (__m128i const* mem_addr);
```

| -           | Description     |
| ----------- | --------------- |
| Instruction | lddqu xmm, m128 |
| CPUID Flags | SSE3            |

## Operation

```
dst[127:0] := MEM[mem_addr+127:mem_addr]
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 0.5              |
