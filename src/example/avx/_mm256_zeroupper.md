`_mm256_zeroupper()`
====================

> Zero the upper 128 bits of all YMM registers; the lower 128 bits of the register are unmodified.

## Synopsis

```c
#include <immintrin.h>

void _mm256_zeroupper (void);
```

## Operation

```
YMM0[MAX:128] := 0
YMM1[MAX:128] := 0
YMM2[MAX:128] := 0
YMM3[MAX:128] := 0
YMM4[MAX:128] := 0
YMM5[MAX:128] := 0
YMM6[MAX:128] := 0
YMM7[MAX:128] := 0
IF _64_BIT_MODE
	YMM8[MAX:128] := 0
	YMM9[MAX:128] := 0
	YMM10[MAX:128] := 0
	YMM11[MAX:128] := 0
	YMM12[MAX:128] := 0
	YMM13[MAX:128] := 0
	YMM14[MAX:128] := 0
	YMM15[MAX:128] := 0
FI
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 4       | 1                |
| Broadwell    | 0       | 1                |
| Haswell      | 0       | 1                |
| Ivy Bridge   | 0       | 1                |
