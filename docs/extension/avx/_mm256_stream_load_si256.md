`_mm256_stream_load_si256(mem: __m256i *): __m256i`
===================================================

> Load 256 bits of integer data from memory into destination using a non-temporal memory hint. mem address must be aligned on a 32 byte boundary or a general protection exception may be generated.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_stream_load_si256 (__m256i const* mem_addr);
```

| -           | Description         |
| ----------- | ------------------- |
| Instruction | vmovntdqa ymm, m256 |
| CPUID Flags | AVX2                |

## Operation

```
dst[255:0] := MEM[mem_addr+255:mem_addr]
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 0.5              |
| Skylake      | 7       | 0.5              |
