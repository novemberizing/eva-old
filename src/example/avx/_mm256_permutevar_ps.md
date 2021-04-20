`_mm256_permutevar_ps(x: __m256, y: __m256i): __m256`
=====================================================

> Shuffle single precision (32 bit) floating point elements in a within 128 bit lanes using the control in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_permutevar_ps (__m256 a, __m256i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpermilps ymm, ymm, ymm |
| CPUID Flags | AVX                     |

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
dst[31:0] := SELECT4(a[127:0], b[1:0])
dst[63:32] := SELECT4(a[127:0], b[33:32])
dst[95:64] := SELECT4(a[127:0], b[65:64])
dst[127:96] := SELECT4(a[127:0], b[97:96])
dst[159:128] := SELECT4(a[255:128], b[129:128])
dst[191:160] := SELECT4(a[255:128], b[161:160])
dst[223:192] := SELECT4(a[255:128], b[193:192])
dst[255:224] := SELECT4(a[255:128], b[225:224])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
