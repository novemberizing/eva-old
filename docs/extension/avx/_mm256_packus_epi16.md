`_mm256_packus_epi16(x: __m256i, y: __m256i): __m256i`
======================================================

> Convert packed signed 16 bit integers from x and y to packed 8 bit integers using unsigned satuation, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_packus_epi16 (__m256i a, __m256i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpackuswb ymm, ymm, ymm |
| CPUID Flags | AVX2                    |


## Opeation

```
dst[7:0] := SaturateU8(a[15:0])
dst[15:8] := SaturateU8(a[31:16])
dst[23:16] := SaturateU8(a[47:32])
dst[31:24] := SaturateU8(a[63:48])
dst[39:32] := SaturateU8(a[79:64])
dst[47:40] := SaturateU8(a[95:80])
dst[55:48] := SaturateU8(a[111:96])
dst[63:56] := SaturateU8(a[127:112])
dst[71:64] := SaturateU8(b[15:0])
dst[79:72] := SaturateU8(b[31:16])
dst[87:80] := SaturateU8(b[47:32])
dst[95:88] := SaturateU8(b[63:48])
dst[103:96] := SaturateU8(b[79:64])
dst[111:104] := SaturateU8(b[95:80])
dst[119:112] := SaturateU8(b[111:96])
dst[127:120] := SaturateU8(b[127:112])
dst[135:128] := SaturateU8(a[143:128])
dst[143:136] := SaturateU8(a[159:144])
dst[151:144] := SaturateU8(a[175:160])
dst[159:152] := SaturateU8(a[191:176])
dst[167:160] := SaturateU8(a[207:192])
dst[175:168] := SaturateU8(a[223:208])
dst[183:176] := SaturateU8(a[239:224])
dst[191:184] := SaturateU8(a[255:240])
dst[199:192] := SaturateU8(b[143:128])
dst[207:200] := SaturateU8(b[159:144])
dst[215:208] := SaturateU8(b[175:160])
dst[223:216] := SaturateU8(b[191:176])
dst[231:224] := SaturateU8(b[207:192])
dst[239:232] := SaturateU8(b[223:208])
dst[247:240] := SaturateU8(b[239:224])
dst[255:248] := SaturateU8(b[255:240])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 1       | 1                |
