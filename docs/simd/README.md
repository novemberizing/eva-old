__SIMD__
========

| function                                                                                             | description |
| ---------------------------------------------------------------------------------------------------- | ----------- |
| `_mm_set_epi16(e7: short, e6: short, e5: short, e4: short, e3: short, e2: short, e1: short, e0: short): __m128i` | set packed 16 bit integers in destination with the supplied values. |
| `_mm_set_epi64x (e1: __int64, e0: __int64): __m128i` | Set packed 64-bit integers in dst with the supplied values. |
| `_mm_load_si128 (mem_addr: __m128i const*): __m128i` | Load 128 bits of integer data from memory into destination. mem_addr must be aligned on a 16 byte boundary or a general protection exception may be generated. |
| `_mm_sub_epi16(a: __m128i, b: __m128i): __m128i` | Subtract packed 16 bit integers in b from packed 16 bit integers in a, and store the results in destiantion. |
| `_mm_sub_epi64 (a: __m128i, b: __m128i): __m128i` | Subtract packed 64 bit integers in b from packed 64 bit integers in a, and store the results in destination. |

----

## `_mm_set_epi16(short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0): m128i`

> Set packed 16-bit integers in dst with the supplied values.

__SYNOPSIS__

```c
#include <emmintrin.h>

__m128i _mm_set_epi16 (short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0)
```

| Subject     | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | SSE2        |


----

## `_mm_set_epi64x (e1: __int64, e0: __int64): __m128i`

> Set packed 64-bit integers in dst with the supplied values.

__SYNOPSIS__

```c
#include <emmintrin.h>

__m128i _mm_set_epi64x (__int64 e1, __int64 e0)
```

| Subject     | Description |
| ----------- | ----------- |
| Instruction | Sequence    |
| CPUID Flags | SSE2        |

__OPERATION__

```
dst[63:0] := e0
dst[127:64] := e1
```

## `_mm_load_si128 (mem_addr: __m128i const*): __m128i`

Load 128 bits of integer data from memory into destination. mem_addr must be aligned on a 16 byte boudnary or a general protection exception may be generated.

```c
#include <emmintrin.h>
__m128i _mm_load_si128 (__m128i const* mem_addr);
```

| Subject     | Description      |
| ----------- | ---------------- |
| Instruction | movdqa xmm, m128 |
| CPUID Flags | SSE2             |

__Operation__

```
dst[127:0] := MEM[mem_addr+127:mem_addr]
```

__Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 6       | 0.5              |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |
| Ivy Bridge   | 1       | 0.5              |

## `_mm_sub_epi16(a: __m128i, b: __m128i): __m128i`

Subtract packed 16 bit integers in b from packed 16 bit integers in a, and store the results in destination.


```c
#include <emmintrin.h>

__m128i _mm_sub_epi16 (__m128i a, __m128i b);
```

| Subject     | Description    |
| ----------- | -------------- |
| Instruction | psubw xmm, xmm |
| CPUID Flags | SSE2           |

__Operation__

```
FOR j := 0 to 7
	i := j*16
	dst[i+15:i] := a[i+15:i] - b[i+15:i]
ENDFOR
```

__Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.5              |
| Haswell      | 1       | 0.5              |
| Ivy Bridge   | 1       | 0.5              |


## `_mm_sub_epi64 (a: __m128i, b: __m128i): __m128i`

Subtract packed 64-bit integers in b from packed 64-bit integers in a, and store the results in dst.

__Synopsis__

```c
#include <emmintrin.h>

__m128i _mm_sub_epi64 (__m128i a, __m128i b);
```

| Subject     | Description    |
| ----------- | -------------- |
| Instruction | psubq xmm, xmm |
| CPUID Flags | SSE2           |

__Operation__

```
FOR j := 0 to 1
	i := j*64
	dst[i+63:i] := a[i+63:i] - b[i+63:i]
ENDFOR
```

__Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 1       | 0.33             |

역시 ASSEMBLY 로 짜야 하는 군


__strlen_avx2

