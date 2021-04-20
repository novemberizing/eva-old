`_mm256_setr_epi8(e31: char, e30: char, e29: char, e28: char, e27: char, e26: char, e25: char, e24: char, e23: char, e22: char, e21: char, e20: char, e19: char, e18: char, e17: char, e16: char, e15: char, e14: char, e13: char, e12: char, e11: char, e10: char, e9: char, e8: char, e7: char, e6: char, e5: char, e4: char, e3: char, e2: char, e1: char, e0: char): __m256i`
============================================================================

> Set packed 8 bit integers in destination with the supplied values in reverse order.

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[7:0] := e31
dst[15:8] := e30
dst[23:16] := e29
dst[31:24] := e28
dst[39:32] := e27
dst[47:40] := e26
dst[55:48] := e25
dst[63:56] := e24
dst[71:64] := e23
dst[79:72] := e22
dst[87:80] := e21
dst[95:88] := e20
dst[103:96] := e19
dst[111:104] := e18
dst[119:112] := e17
dst[127:120] := e16
dst[135:128] := e15
dst[143:136] := e14
dst[151:144] := e13
dst[159:152] := e12
dst[167:160] := e11
dst[175:168] := e10
dst[183:176] := e9
dst[191:184] := e8
dst[199:192] := e7
dst[207:200] := e6
dst[215:208] := e5
dst[223:216] := e4
dst[231:224] := e3
dst[239:232] := e2
dst[247:240] := e1
dst[255:248] := e0
dst[MAX:256] := 0
```
