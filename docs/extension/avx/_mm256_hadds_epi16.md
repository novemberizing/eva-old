`_mm256_hadds_epi16(x: __m256i, y: __m256i): __m256i`
=====================================================

> Horizontally add adjacent pairs of signed 16 bit integers in x and y using saturation, and pack the signed 16 bit results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_hadds_epi16(__m256i x, __m256i y);
```

| -           | Description            |
| ----------- | ---------------------- |
| Instruction | vphaddsw ymm, ymm, ymm |
| CPUID Flags | AVX2                   |

## Operation

```
dst[15:0] := Saturate16(a[31:16] + a[15:0])
dst[31:16] := Saturate16(a[63:48] + a[47:32])
dst[47:32] := Saturate16(a[95:80] + a[79:64])
dst[63:48] := Saturate16(a[127:112] + a[111:96])
dst[79:64] := Saturate16(b[31:16] + b[15:0])
dst[95:80] := Saturate16(b[63:48] + b[47:32])
dst[111:96] := Saturate16(b[95:80] + b[79:64])
dst[127:112] := Saturate16(b[127:112] + b[111:96])
dst[143:128] := Saturate16(a[159:144] + a[143:128])
dst[159:144] := Saturate16(a[191:176] + a[175:160])
dst[175:160] := Saturate16(a[223:208] + a[207:192])
dst[191:176] := Saturate16(a[255:240] + a[239:224])
dst[207:192] := Saturate16(b[159:144] + b[143:128])
dst[223:208] := Saturate16(b[191:176] + b[175:160])
dst[239:224] := Saturate16(b[223:208] + b[207:192])
dst[255:240] := Saturate16(b[255:240] + b[239:224])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 3       | 2                |
| Broadwell    | 3       | 2                |
| Haswell      | 3       | 2                |
