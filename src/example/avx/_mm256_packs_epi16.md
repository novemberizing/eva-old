`_mm256_packs_epi16(x: __m256i, y: __m256i): __m256i`
=====================================================

> Convert packed signed 16 bit integers from x and y packed 8 bit integers using signed saturation, and store the result in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_packs_epi16 (__m256i a, __m256i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpacksswb ymm, ymm, ymm |
| CPUID Flags | AVX2                    |

## Operation

```
dst[7:0] := Saturate8(a[15:0])
dst[15:8] := Saturate8(a[31:16])
dst[23:16] := Saturate8(a[47:32])
dst[31:24] := Saturate8(a[63:48])
dst[39:32] := Saturate8(a[79:64])
dst[47:40] := Saturate8(a[95:80])
dst[55:48] := Saturate8(a[111:96])
dst[63:56] := Saturate8(a[127:112])
dst[71:64] := Saturate8(b[15:0])
dst[79:72] := Saturate8(b[31:16])
dst[87:80] := Saturate8(b[47:32])
dst[95:88] := Saturate8(b[63:48])
dst[103:96] := Saturate8(b[79:64])
dst[111:104] := Saturate8(b[95:80])
dst[119:112] := Saturate8(b[111:96])
dst[127:120] := Saturate8(b[127:112])
dst[135:128] := Saturate8(a[143:128])
dst[143:136] := Saturate8(a[159:144])
dst[151:144] := Saturate8(a[175:160])
dst[159:152] := Saturate8(a[191:176])
dst[167:160] := Saturate8(a[207:192])
dst[175:168] := Saturate8(a[223:208])
dst[183:176] := Saturate8(a[239:224])
dst[191:184] := Saturate8(a[255:240])
dst[199:192] := Saturate8(b[143:128])
dst[207:200] := Saturate8(b[159:144])
dst[215:208] := Saturate8(b[175:160])
dst[223:216] := Saturate8(b[191:176])
dst[231:224] := Saturate8(b[207:192])
dst[239:232] := Saturate8(b[223:208])
dst[247:240] := Saturate8(b[239:224])
dst[255:248] := Saturate8(b[255:240])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
