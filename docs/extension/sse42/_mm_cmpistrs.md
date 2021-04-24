`_mm_cmpistrs(x: __m128i, y: __m128i, imm8: const int): int`
============================================================

> Compare packed strings with implicit lengths in x and y using the control in imm8, and returns 1 if any character in x was null, and 0 otherwise.

imm can be a combination of:

| Mask                           | Description                              |
| ------------------------------ | ---------------------------------------- |
| _SIDD_UBYTE_OPS                | unsigned 8-bit characters                |
| _SIDD_UWORD_OPS                | unsigned 16-bit characters               |
| _SIDD_SBYTE_OPS                | signed 8-bit characters                  |
| _SIDD_SWORD_OPS                | signed 16-bit characters                 |
| _SIDD_CMP_EQUAL_ANY            | compare equal any                        |
| _SIDD_CMP_RANGES               | compare ranges                           |
| _SIDD_CMP_EQUAL_EACH           | compare equal each                       |
| _SIDD_CMP_EQUAL_ORDERED        | compare equal ordered                    |
| _SIDD_NEGATIVE_POLARITY        | negate results                           |
| _SIDD_MASKED_NEGATIVE_POLARITY | negate results only before end of string |
| _SIDD_LEAST_SIGNIFICANT        | index only: return last significant bit  |
| _SIDD_MOST_SIGNIFICANT         | index only: return most significant bit  |
| _SIDD_BIT_MASK                 | mask only: return bit mask               |
| _SIDD_UNIT_MASK                | mask only: return byte/word mask         |

## Synopsis

```c
#include <nmmintrin.h>

int _mm_cmpistrs (__m128i a, __m128i b, const int imm8)
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | pcmpistri xmm, xmm, imm8 |
| CPUID Flags | SSE4.2                   |

## Operation

```
size := (imm8[0] ? 16 : 8) // 8 or 16-bit characters
UpperBound := (128 / size) - 1
aInvalid := 0
FOR i := 0 to UpperBound
	m := i*size
	IF a[m+size-1:m] == 0
		aInvalid := 1
	FI
ENDFOR
dst := aInvalid
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 10      | 3                |