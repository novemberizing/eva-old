`_mm256_setr_epi16(e15: short, e14: short, e13: short, e12: short, e11: short, e10: short, e9: short, e8: short, e7: short, e6: short, e5: short, e4: short, e3: short, e2: short, e1: short, e0: short): __mm256i`
============================================================================

> Set packed 16 bit integers in destination with the supplied values in reverse order.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_setr_epi16 (short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8, short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[15:0] := e15
dst[31:16] := e14
dst[47:32] := e13
dst[63:48] := e12
dst[79:64] := e11
dst[95:80] := e10
dst[111:96] := e9
dst[127:112] := e8
dst[143:128] := e7
dst[159:144] := e6
dst[175:160] := e5
dst[191:176] := e4
dst[207:192] := e3
dst[223:208] := e2
dst[239:224] := e1
dst[255:240] := e0
dst[MAX:256] := 0
```
