`_mm256_round_pd(x: __m256d, rounding: int): __m256d`
=====================================================

> Round the packed double precision (64 bit) floating point elements in a using the rounding parameter, and store the results as packed double precision floating point elements in destination.
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

__m256d _mm256_round_pd (__m256d a, int rounding);
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vroundpd ymm, ymm, imm8 |
| CPUID Flags | AVX                     |

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := ROUND(a[i+63:i], rounding)
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
