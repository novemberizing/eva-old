`_mm256_dp_ps(x: __m256, y: __m256, imm8: const int): __m256`
=============================================================

> Conditionally multiply the packed single precision (32 bit) floating point elements in x and y using the high 4 bits in imm8, sum the four products, and conditionally store the sum in destination using the low 4 bits of imm8.

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_dp_ps(__m256 x, __m256 y, const int imm8);
```

| -           | Description               |
| ----------- | ------------------------- |
| Instruction | vdpps ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                       |

## Operation

```
DEFINE DP(a[127:0], b[127:0], imm8[7:0]) {
	FOR j := 0 to 3
		i := j*32
		IF imm8[(4+j)%8]
			temp[i+31:i] := a[i+31:i] * b[i+31:i]
		ELSE
			temp[i+31:i] := FP32(0.0)
		FI
	ENDFOR
	
	sum[31:0] := (temp[127:96] + temp[95:64]) + (temp[63:32] + temp[31:0])
	
	FOR j := 0 to 3
		i := j*32
		IF imm8[j%8]
			tmpdst[i+31:i] := sum[31:0]
		ELSE
			tmpdst[i+31:i] := FP32(0.0)
		FI
	ENDFOR
	RETURN tmpdst[127:0]
}
dst[127:0] := DP(a[127:0], b[127:0], imm8[7:0])
dst[255:128] := DP(a[255:128], b[255:128], imm8[7:0])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 15      | 1.5              |
| Broadwell    | 12      | 2                |
| Haswell      | 14      | 2                |
| Ivy Bridge   | 12      | 2                |
