`_mm_cmp_pd(x: __m128d, y: __m128d, imm8: const int): __m128d`
==============================================================

> Compare packed double precision (64 bit) floating point elements in x and y based on the comparison operand specified by imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128d _mm_cmp_pd(__m128d x, __m128d y, const int imm8);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vcmppd xmm, xmm, xmm, imm8 |
| CPUID Flags | AVX                        |

## PARAMETERS

| PARAMETER       | VALUE | DESCRIPTION                                          |
| --------------- | ----- | ---------------------------------------------------- |
| `_CMP_EQ_OQ`    | 0x00  | Equal (ordered, non signaling)                       |
| `_CMP_LT_OS`    | 0x01  | Less than (ordered, signaling)                       |
| `_CMP_LE_OS`    | 0x02  | Less than or equal (ordered, signaling)              |
| `_CMP_UNORD_Q`  | 0x03  | Unordered (non signaling)                            |
| `_CMP_NEQ_UQ`   | 0x04  | Not equal (unordered, non signaling)                 |
| `_CMP_NLT_US`   | 0x05  | Not less than (unordered, signaling)                 |
| `_CMP_NLE_US`   | 0x06  | Not less than or equal (unordered , signaling)       |
| `_CMP_ORD_Q`    | 0x07  | Ordered (nonsignaling)                               |
| `_CMP_EQ_UQ`    | 0x08  | Equal (unordered, non signaling)                     |
| `_CMP_NGE_US`   | 0x09  | Not greater than or equal (unordered, signaling)     |
| `_CMP_NGT_US`   | 0x0a  | Not greater than (unordered, signaling)              |
| `_CMP_FALSE_OQ` | 0x0b  | False (ordered, non signaling)                       |
| `_CMP_NEQ_OQ`   | 0x0c  | Not equal (ordered, non signaling)                   |
| `_CMP_GE_OS`    | 0x0d  | Greater than or equal (ordered, signaling)           |
| `_CMP_GT_OS`    | 0x0e  | Greater than (ordered, signaling)                    |
| `_CMP_TRUE_UQ`  | 0x0f  | True (unordered, non signaling)                      |
| `_CMP_EQ_OS`    | 0x10  | Equal (orderedm, signaling)                          |
| `_CMP_LT_OQ`    | 0x11  | Less than (ordered, non signaling)                   |
| `_CMP_LE_OQ`    | 0x12  | Less than or equal (ordered, non signaling)          |
| `_CMP_UNORD_S`  | 0x13  | Unordered (signaling)                                |
| `_CMP_NEQ_US`   | 0x14  | Not equal (unordered, signaling)                     |
| `_CMP_NLT_UQ`   | 0x15  | Not less than (unordered, non signaling)             |
| `_CMP_NLE_UQ`   | 0x16  | Not less than or equal (unordered, non signaling)    |
| `_CMP_ORD_S`    | 0x17  | Ordered (signaling)                                  |
| `_CMP_EQ_US`    | 0x18  | Equal (unordered, signaling)                         |
| `_CMP_NGE_UQ`   | 0x19  | Not greater than or equal (unordered, non signaling) |
| `_CMP_NGT_UQ`   | 0x1a  | Not greater than (unordered, non signaling)          |
| `_CMP_FALSE_OS` | 0x1b  | False (ordered, signaling)                           |
| `_CMP_NEQ_OS`   | 0x1c  | Not equal (ordered, signaling)                       |
| `_CMP_GE_OQ`    | 0x1d  | Greater than or equal (ordered, non signaling)       |
| `_CMP_GT_OQ`    | 0x1e  | Greater than (ordered, non signaling)                |
| `_CMP_TRUE_US`  | 0x1f  | True (unordered, signaling)                          |

## Operation

```
CASE (imm8[4:0]) OF
0: OP := _CMP_EQ_OQ
1: OP := _CMP_LT_OS
2: OP := _CMP_LE_OS
3: OP := _CMP_UNORD_Q 
4: OP := _CMP_NEQ_UQ
5: OP := _CMP_NLT_US
6: OP := _CMP_NLE_US
7: OP := _CMP_ORD_Q
8: OP := _CMP_EQ_UQ
9: OP := _CMP_NGE_US
10: OP := _CMP_NGT_US
11: OP := _CMP_FALSE_OQ
12: OP := _CMP_NEQ_OQ
13: OP := _CMP_GE_OS
14: OP := _CMP_GT_OS
15: OP := _CMP_TRUE_UQ
16: OP := _CMP_EQ_OS
17: OP := _CMP_LT_OQ
18: OP := _CMP_LE_OQ
19: OP := _CMP_UNORD_S
20: OP := _CMP_NEQ_US
21: OP := _CMP_NLT_UQ
22: OP := _CMP_NLE_UQ
23: OP := _CMP_ORD_S
24: OP := _CMP_EQ_US
25: OP := _CMP_NGE_UQ 
26: OP := _CMP_NGT_UQ 
27: OP := _CMP_FALSE_OS 
28: OP := _CMP_NEQ_OS 
29: OP := _CMP_GE_OQ
30: OP := _CMP_GT_OQ
31: OP := _CMP_TRUE_US
ESAC
FOR j := 0 to 1
	i := j*64
	dst[i+63:i] := ( a[i+63:i] OP b[i+63:i] ) ? 0xFFFFFFFFFFFFFFFF : 0
ENDFOR
dst[MAX:128] := 0
```

## See

[How to choose AVX compare predicate variants](https://stackoverflow.com/questions/16988199/how-to-choose-avx-compare-predicate-variants)

When either operand is NaN, ordered vs unordered dictates the result value.

Ordered comparisons return false for NaN operands.

- `_CMP_EQ_OQ` of 1.0 and 1.0 gives true
- `_CMP_EQ_OQ` of NaN and 1.0 gives false.
- `_CMP_EQ_OQ` of 1.0 and NaN gives false.
- `_CMP_EQ_OQ` of NaN and NaN gives false.

Unordered comparison returns true for NaN operands.

- `_CMP_EQ_UQ` of 1.0 and 1.0 gives true.
- `_CMP_EQ_UQ` of NaN and 1.0 gives true.
- `_CMP_EQ_UQ` of 1.0 and NaN gives true.
- `_CMP_EQ_UQ` of NaN and NaN gives true.

The difference between signaling vs non signaling only impacts the value the MXCSR. To observe the effect, you'd need to clear the MXCSR, perform one or more comparisons, then read from the MXCSR (thanks to Peter Cordes for clarifying this!).

The order of the enum values is pretty confusing. It helps to put them in a table.

| comparison | ordered (non-signalling)  | unordered (non-signalling) |
| ---------- | ------------------------- | -------------------------- |
| a < b      | `_CMP_LT_OQ`              | `_CMP_NGE_UQ`              |
| a <= b     | `_CMP_LE_OQ`              | `_CMP_NGT_UQ`              |
| a == b     | `_CMP_EQ_OQ`              | `_CMP_EQ_UQ`               |
| a != b     | `_CMP_NEQ_OQ`             | `_CMP_NEQ_UQ`              |
| a >= b     | `_CMP_GE_OQ`              | `_CMP_NLT_UQ`              |
| a > b      | `_CMP_GT_OQ`              | `_CMP_NLE_UQ`              |
| true       | `_CMP_ORD_Q`              | `_CMP_TRUE_UQ (useless)`   |
| false      | `_CMP_FALSE_OQ (useless)` | `_CMP_UNORD_Q`             |

With MXCSR signaling:

| comparison | ordered (signalling)      | unordered (signalling)   |
| ---------- | ------------------------- | ------------------------ |
| a < b      | `_CMP_LT_OS`              | `_CMP_NGE_US`            |
| a <= b     | `_CMP_LE_OS`              | `_CMP_NGT_US`            |
| a == b     | `_CMP_EQ_OS`              | `_CMP_EQ_US`             |
| a != b     | `_CMP_NEQ_OS`             | `_CMP_NEQ_US`            |
| a >= b     | `_CMP_GE_OS`              | `_CMP_NLT_US`            |
| a > b      | `_CMP_GT_OS`              | `_CMP_NLE_US`            |
| true       | `_CMP_ORD_S`              | `_CMP_TRUE_US (useless)` |
| false      | `_CMP_FALSE_OS (useless)` | `_CMP_UNORD_S`           |

[MXCSR State Management Instructions (SSE)](https://docs.oracle.com/cd/E19120-01/open.solaris/817-5477/epmpe/index.html)

The MXCSR state management instructions save and restore the state of the MXCSR control and status register.
