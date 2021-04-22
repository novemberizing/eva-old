`_mm256_unpackhi_epi8(x: __m256i, y: __m256i): __m256i`
=======================================================

> Unpack and interleave 8 bit integers from the high half of each 128 bit lane in x and y, and store the results in destination.

## Synopsis

```c
#include <immintrin.h>

__m256i _mm256_unpackhi_epi8 (__m256i a, __m256i b);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vpunpckhbw ymm, ymm, ymm |
| CPUID Flags | AVX2                     |

## Operation

```
DEFINE INTERLEAVE_HIGH_BYTES(src1[127:0], src2[127:0]) {
	dst[7:0] := src1[71:64] 
	dst[15:8] := src2[71:64] 
	dst[23:16] := src1[79:72] 
	dst[31:24] := src2[79:72] 
	dst[39:32] := src1[87:80] 
	dst[47:40] := src2[87:80] 
	dst[55:48] := src1[95:88] 
	dst[63:56] := src2[95:88] 
	dst[71:64] := src1[103:96] 
	dst[79:72] := src2[103:96] 
	dst[87:80] := src1[111:104] 
	dst[95:88] := src2[111:104] 
	dst[103:96] := src1[119:112] 
	dst[111:104] := src2[119:112] 
	dst[119:112] := src1[127:120] 
	dst[127:120] := src2[127:120] 
	RETURN dst[127:0]	
}
dst[127:0] := INTERLEAVE_HIGH_BYTES(a[127:0], b[127:0])
dst[255:128] := INTERLEAVE_HIGH_BYTES(a[255:128], b[255:128])
dst[MAX:256] := 0
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | -                |
| Skylake      | 1       | 1                |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |

