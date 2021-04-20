`_mm256_set_epi16(e15: short, e14: short, e13: short, e12: short, e11: short, e10: short, e9: short, e8: short, e7: short, e6: short, e5: short, e4: short, e3: short, e2: short, e1: short, e0: short): __m256i`
======================================================================================================================================

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set_epi16 (short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8, short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

##  Operation

```
dst[15:0] := e0
dst[31:16] := e1
dst[47:32] := e2
dst[63:48] := e3
dst[79:64] := e4
dst[95:80] := e5
dst[111:96] := e6
dst[127:112] := e7
dst[143:128] := e8
dst[159:144] := e9
dst[175:160] := e10
dst[191:176] := e11
dst[207:192] := e12
dst[223:208] := e13
dst[239:224] := e14
dst[255:240] := e15
dst[MAX:256] := 0
```
