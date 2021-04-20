`_mm256_packs_epi32(x: __m256i, y: __m256i): __m256i`
=====================================================

> Convert packed signed 32 bit integers from x and y to packed 16 bit integers using signed saturation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_packs_epi32 (__m256i a, __m256i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpackssdw ymm, ymm, ymm |
| CPUID Flags | AVX2                    |

## Operation

```
dst[15:0] := Saturate16(a[31:0])
dst[31:16] := Saturate16(a[63:32])
dst[47:32] := Saturate16(a[95:64])
dst[63:48] := Saturate16(a[127:96])
dst[79:64] := Saturate16(b[31:0])
dst[95:80] := Saturate16(b[63:32])
dst[111:96] := Saturate16(b[95:64])
dst[127:112] := Saturate16(b[127:96])
dst[143:128] := Saturate16(a[159:128])
dst[159:144] := Saturate16(a[191:160])
dst[175:160] := Saturate16(a[223:192])
dst[191:176] := Saturate16(a[255:224])
dst[207:192] := Saturate16(b[159:128])
dst[223:208] := Saturate16(b[191:160])
dst[239:224] := Saturate16(b[223:192])
dst[255:240] := Saturate16(b[255:224])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 1       | 1                |
