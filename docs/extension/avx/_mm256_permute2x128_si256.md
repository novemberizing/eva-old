`_mm256_permute2x128_si256(x: __m256i, y: __m256i, imm8: const int): __m256i`
=============================================================================

> Shuffle 128 bits (composed of integer data) selected by imm8 from x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_permute2x128_si256 (__m256i a, __m256i b, const int imm8);
```

| -           | Description                    |
| ----------- | ------------------------------ |
| Instruction | vperm2i128 ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX2                           |

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
