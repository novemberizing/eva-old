`_mm256_stream_ps(mem: float *, x: __m256)`
===========================================

> Store 256 bits (composed of 8 packed single precision (32 bit) floating point elements) from x into memory using a non temporal memory hint. mem address must be aligned on a 32 byte boundary or a general protection exception may be generated.

| -           | Description        |
| ----------- | ------------------ |
| Instruction | vmovntps m256, ymm |
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
