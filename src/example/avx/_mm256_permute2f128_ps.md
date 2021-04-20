`_mm256_permute2f128_ps (x: __m256, y: __m256, imm8: int): __m256`
==================================================================

> Suffle 128 bits (composed of 4 packed single precision (32 bit) floating point elements) selected by imm8 from x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_permute2f128_ps (__m256 a, __m256 b, int imm8);
```

| -           | Description                    |
| ----------- | ------------------------------ |
| Instruction | vperm2f128 ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                            |

## Operation

```
DEFINE SELECT4(src1, src2, control) {
	CASE(control[1:0]) OF
	0:	tmp[127:0] := src1[127:0]
	1:	tmp[127:0] := src1[255:128]
	2:	tmp[127:0] := src2[127:0]
	3:	tmp[127:0] := src2[255:128]
	ESAC
	IF control[3]
		tmp[127:0] := 0
	FI
	RETURN tmp[127:0]
}
dst[127:0] := SELECT4(a[255:0], b[255:0], imm8[3:0])
dst[255:128] := SELECT4(a[255:0], b[255:0], imm8[7:4])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 2       | 1                |
