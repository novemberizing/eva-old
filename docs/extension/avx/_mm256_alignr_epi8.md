`_mm256_alignr_epi8(x: __m256i, y: __m256i, const int imm8): __m256i`
=====================================================================

> Concatenate pairs of 16 byte blocks in x and y into a 32 byte temporary result, shift the result right by imm8 bytes, and store the low 16 bytes in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_alignr_epi8(__m256i x, __m256i y, const int imm8);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vpalignr ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX2                         |

##Operation

```
FOR j := 0 to 1
	i := j*128
	tmp[255:0] := ((a[i+127:i] << 128)[255:0] OR b[i+127:i]) >> (imm8*8)
	dst[i+127:i] := tmp[127:0]
ENDFOR
dst[MAX:256] := 0
```
