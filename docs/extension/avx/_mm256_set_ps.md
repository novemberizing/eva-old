`_mm256_set_ps(e7: float, e6: float, e5: float, e4: float, e3: float, e2: float, e1: float, e0: float): __m256`
===============================================================================================================

> Set packed single precision (32 bit) floating point elements in destination with the supplied values.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_set_ps (float e7, float e6, float e5, float e4, float e3, float e2, float e1, float e0);
```

| -           | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | AVX         |

## Operation

```
dst[31:0] := e0
dst[63:32] := e1
dst[95:64] := e2
dst[127:96] := e3
dst[159:128] := e4
dst[191:160] := e5
dst[223:192] := e6
dst[255:224] := e7
dst[MAX:256] := 0
```
