`_mm256_packus_epi32(x: __m256i, y: __m256i): __m256i`
======================================================

> Convert packed signed 32 bit integers from x and y to packed 16 bit integers using unsigned satuation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_packus_epi32 (__m256i a, __m256i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpackusdw ymm, ymm, ymm |
| CPUID Flags | AVX2                    |

## Operation

```
dst[15:0] := SaturateU16(a[31:0])
dst[31:16] := SaturateU16(a[63:32])
dst[47:32] := SaturateU16(a[95:64])
dst[63:48] := SaturateU16(a[127:96])
dst[79:64] := SaturateU16(b[31:0])
dst[95:80] := SaturateU16(b[63:32])
dst[111:96] := SaturateU16(b[95:64])
dst[127:112] := SaturateU16(b[127:96])
dst[143:128] := SaturateU16(a[159:128])
dst[159:144] := SaturateU16(a[191:160])
dst[175:160] := SaturateU16(a[223:192])
dst[191:176] := SaturateU16(a[255:224])
dst[207:192] := SaturateU16(b[159:128])
dst[223:208] := SaturateU16(b[191:160])
dst[239:224] := SaturateU16(b[223:192])
dst[255:240] := SaturateU16(b[255:224])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
