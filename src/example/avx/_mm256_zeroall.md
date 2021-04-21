`_mm256_zeroall()`
==================

> Zero the contents of all XMM or YMM registers.

## Synopsis

```c
#include <immintrin.h>

void _mm256_zeroall (void)
```

## Operation

```
YMM0[MAX:0] := 0
YMM1[MAX:0] := 0
YMM2[MAX:0] := 0
YMM3[MAX:0] := 0
YMM4[MAX:0] := 0
YMM5[MAX:0] := 0
YMM6[MAX:0] := 0
YMM7[MAX:0] := 0
IF _64_BIT_MODE
	YMM8[MAX:0] := 0
	YMM9[MAX:0] := 0
	YMM10[MAX:0] := 0
	YMM11[MAX:0] := 0
	YMM12[MAX:0] := 0
	YMM13[MAX:0] := 0
	YMM14[MAX:0] := 0
	YMM15[MAX:0] := 0
FI
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 16      | 4                |
| Broadwell    | -       | 8                |
| Haswell      | -       | 8                |
| Ivy Bridge   | -       | 9                |
