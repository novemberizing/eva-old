`_mm256_set_epi8(e31: char, e30: char, e29: char, e28: char, e27: char, e26: char, e25: char, e24: char, e23: char, e22: char, e21: char, e20: char, e19: char, e18: char, e17: char, e16: char, e15: char, e14: char, e13: char, e12: char, e11: char, e10: char, e9: char, e8: char, e7: char, e6: char, e5: char, e4: char, e3: char, e2: char, e1: char, e0: char): __m256i`
======================================================================================================================================

> Set packed 8-bit integers in destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_set_epi8 (char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24, char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16, char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8, char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[7:0] := e0
dst[15:8] := e1
dst[23:16] := e2
dst[31:24] := e3
dst[39:32] := e4
dst[47:40] := e5
dst[55:48] := e6
dst[63:56] := e7
dst[71:64] := e8
dst[79:72] := e9
dst[87:80] := e10
dst[95:88] := e11
dst[103:96] := e12
dst[111:104] := e13
dst[119:112] := e14
dst[127:120] := e15
dst[135:128] := e16
dst[143:136] := e17
dst[151:144] := e18
dst[159:152] := e19
dst[167:160] := e20
dst[175:168] := e21
dst[183:176] := e22
dst[191:184] := e23
dst[199:192] := e24
dst[207:200] := e25
dst[215:208] := e26
dst[223:216] := e27
dst[231:224] := e28
dst[239:232] := e29
dst[247:240] := e30
dst[255:248] := e31
dst[MAX:256] := 0
```
