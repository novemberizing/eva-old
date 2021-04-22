`_mm_permutevar_ps(x: __m128, y: __m128): __m128`
=================================================

> Shuffle single precision (32 bit) floating point elements in x using the control in y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m128 _mm_permutevar_ps (__m128 a, __m128i b);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vpermilps xmm, xmm, xmm |
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
dst[MAX:128] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |
