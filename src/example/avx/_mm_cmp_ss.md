`_mm_cmp_ss(x: __m128, y: __m128, imm8: const int): __m128`
===========================================================

> Compare the lower single precision (32 bit) floating point element in x and y based on the comparison operand specified by imm8, store the result in the lower element of destination, and copy the upper 3 packed elements from x to upper elements of destination.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm_cmp_ss (__m128 a, __m128 b, const int imm8)
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vcmpss xmm, xmm, xmm, imm8 |
| CPUID Flags | AVX                        |

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
dst[31:0] := ( a[31:0] OP b[31:0] ) ? 0xFFFFFFFF : 0
dst[127:32] := a[127:32]
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |