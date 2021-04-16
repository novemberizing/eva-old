`_mm256_cmp_pd(x: __m256d, y: __m256d, imm8: const int): __m256d`
=================================================================

> Compare packed double precision (64 bit) floating point elements in x and y based on the comparison operand psecified by imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256d _mm256_cmp_pd(__m256d x, __m256d y, const int imm8);
```

| -           | Description                |
| ----------- | -------------------------- |
| Instruction | vcmppd ymm, ymm, ymm, imm8 |
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
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := ( a[i+63:i] OP b[i+63:i] ) ? 0xFFFFFFFFFFFFFFFF : 0
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |
