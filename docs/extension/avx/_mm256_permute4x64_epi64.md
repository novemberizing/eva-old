`_mm256_permute4x64_epi64(x: __m256i, imm8: const int): __m256i`
================================================================

> Shuffle 64 bit integer in a across lanes using the control in imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_permute4x64_epi64 (__m256i a, const int imm8);
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vpermq ymm, ymm, imm8 |
| CPUID Flags | AVX2                  |

## Operation

```
DEFINE SELECT4(src, control) {
	CASE(control[1:0]) OF
	0:	tmp[63:0] := src[63:0]
	1:	tmp[63:0] := src[127:64]
	2:	tmp[63:0] := src[191:128]
	3:	tmp[63:0] := src[255:192]
	ESAC
	RETURN tmp[63:0]
}
dst[63:0] := SELECT4(a[255:0], imm8[1:0])
dst[127:64] := SELECT4(a[255:0], imm8[3:2])
dst[191:128] := SELECT4(a[255:0], imm8[5:4])
dst[255:192] := SELECT4(a[255:0], imm8[7:6])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 3       | 1                |
| Skylake      | 3       | 1                |
