`_mm256_round_ps(x: __m256, rounding: int): __m256`
===================================================

> Rount the packed single precision (32 bit) floating point elements in a using the rounding parameter, and store the results as packed single precision floating point elements in destination.
>
> Rounding is done according to the rounding[3:0] parameter, which can be one of:
>
> - (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC) // round to nearest, and suppress exceptions
> - (_MM_FROUND_TO_NEG_INF |_MM_FROUND_NO_EXC)     // round down, and suppress exceptions
> - (_MM_FROUND_TO_POS_INF |_MM_FROUND_NO_EXC)     // round up, and suppress exceptions
> - (_MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC)        // truncate, and suppress exceptions
> - _MM_FROUND_CUR_DIRECTION // use MXCSR.RC; see _MM_SET_ROUNDING_MODE

## Synopsis

```c
#include <immintrin.h>

__m256 _mm256_round_ps (__m256 a, int rounding);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vroundps ymm, ymm, imm8 |
| CPUID Flags | AVX                     |

## Operation

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := ROUND(a[i+31:i], rounding)
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 8       | 1                |
| Skylake      | 8       | 1                |
| Broadwell    | 6       | 2                |
| Haswell      | 6       | 2                |
| Ivy Bridge   | 3       | 1                |
