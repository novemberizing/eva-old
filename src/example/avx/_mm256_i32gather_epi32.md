`_mm256_i32gather_epi32(base: int const *, vindex: __m256i, scale: const int): __m256i`
=======================================================================================

> Gather 32 bit integers from memory using 32 bit indices, 32 bit elements are loaded from addresses starting at base address and offset by each 32 bit element in vindex (each index is scale by the factor in scale). Gathered elements are merged into destination. scale should be 1, 2, 4, or 8.

## Operation

```
FOR j := 0 to 7
    i := j * 32
    m := j * 32
    addr := add + SignExtend64(vindex[vindex[m+31:m]]) * ZeroExtend64(scale) * 8
    dst[i+31:i] := MEM[addr+31:addr]
ENDFOR
dst[MAX:256] = 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Broadwell    | ~19     | ~6               |
| Haswell      | ~20     | ~10              |

