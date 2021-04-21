`_mm256_shuffle_ps(x: __m256, y: __m256, imm8: const int)`
==========================================================

> Shuffle single precision (32 bit) floating point elements in x within 128 bit lanes using the control in imm8, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_shuffle_ps (__m256 a, __m256 b, const int imm8);
```

| -           | Description                 |
| ----------- | --------------------------- |
| Instruction | vshufps ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                         |

## Operation

```
DEFINE SELECT4(src, control) {
	CASE(control[1:0]) OF
	0:	tmp[31:0] := src[31:0]
	1:	tmp[31:0] := src[63:32]
	2:	tmp[31:0] := src[95:64]
	3:	tmp[31:0] := src[127:96]
	ESAC
	RETURN tmp[31:0]
}
dst[31:0] := SELECT4(a[127:0], imm8[1:0])
dst[63:32] := SELECT4(a[127:0], imm8[3:2])
dst[95:64] := SELECT4(b[127:0], imm8[5:4])
dst[127:96] := SELECT4(b[127:0], imm8[7:6])
dst[159:128] := SELECT4(a[255:128], imm8[1:0])
dst[191:160] := SELECT4(a[255:128], imm8[3:2])
dst[223:192] := SELECT4(b[255:128], imm8[5:4])
dst[255:224] := SELECT4(b[255:128], imm8[7:6])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
