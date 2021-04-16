`_mm256_cmpeq_epi64(x: __m256i, y: __m256i): __m256i`
=====================================================

> Compare packed 64 bit integers in x and y for equality, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_cmpeq_epi64(__m256i x, __m256i y);
```

## Operation

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := ( a[i+63:i] == b[i+63:i] ) ? 0xFFFFFFFFFFFFFFFF : 0
ENDFOR
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.5              |
| Skylake      | 1       | 0.5              |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
