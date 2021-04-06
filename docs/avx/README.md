
| Function                                                            | Description |
| ------------------------------------------------------------------- | ----------- |
| `_mm256_add_pd(a: __m256d, b: __m256d): __m256d`                    | Add packed double precision (64 bit) floating point elements in a and b, and store the results in destination. |
| `_mm256_add_ps(a: __m256, b: __m256d): __m256d`                     | Add packed single precision (64 bit) floating point elements in a and b, and store the resutls in destination. |
| `_mm256_addsub_pd(a: __m256d, b: __m256d): __m256d`                 | Alternatively add and subtract packed double-precision (64-bit) floating-point elements in a to/form packed elements in b, and store the results in destination. |
| `_mm256_addsub_ps(a: __m256, b: __m256): __m256`                    | Alternatively add and subtract packed single precision (32 bit) floating point elements in a to/from apcked elements in b, and store the results in destination. |
| `_mm256_and_pd(a: __m256d, b: __m256d): __m256d`                    | Compute the bitwise AND of packed double precision (64 bit) floating point elements in a and b, and store the results in destination. |
| `_mm256_and_ps(a: __m256, b: __m256): __m256`                       | Compute the bitwise AND of packed single precision (32 bit) floating elements in a and b, and store the results in destination. |
| `_mm256_andnot_pd(a: __m256d, b: __m256d): __m256d`                 | Compute the bitwise NOT of packed double precision (64 bit) floating point elements in a and then AND with b, and store the results in destination. |
| `_mm256_andnot_ps(a: __m256, b: __m256): __m256`                    | Compute the bitwise NOT of packed single precision (32 bit) floating point elements in a and then AND with b, and store the results in destination. |
| `_mm256_blend_pd(a: __m256d, b: __m256d, imm8: const int): __m256d` | Blend packed double precision (64 bit) floating point elements from a and b using control mask imm8, and store the results in destination. |
| `_mm256_blend_ps(a: __m256, b: __m256, const int imm8): __m256`     | Blend packed single precision (32 bit) floating point elements from a and b using control mask imm8, and store the results in destination. |
| `_mm256_blendv_ps(a: __m256, b: __m256, mask: __m256): __m256`      | Blend packed single precision (32 bit) floating point elements from a and b using mask, and store the results in destination. |
| `_mm256_broadcast_pd(mem_addr: __m128d const *): __m256d`           | Broadcast 128 bits from memory (composed of 2 packed double precision (64 bit) floating point elements) to all elements of destination. |
| `_mm256_broadcast_ps(mem_addr: __m128 const *): __m256`             | Broadcast 128 bits from memory (composed of 4 packed single precision (32 bit) floating point elements) to all elements of destination. |
| `_mm256_broadcast_sd(mem_addr: double const *): __m256d`            | Broadcast a double precision (64 bit) floating point element from memory to all elements of destination. |
| `_mm_broadcast_ss(mem_addr: float const *): __m128`                 | Broadcast a single precision (32 bit) floating point element from memory to all elements of destination. |
| `_mm256_broadcast_ss(mem_addr: float const *): __m256`              | Broadcast a single precision (32 bit) floating point element from emeory to all elements of destination. |
| `_mm256_castpd_ps(a: __m256d): __m256`                              | Cast vector of type `__m256d` to type `__m256`. This intrinsic is only used for compliation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castpd_si256(a: __m256d): __m256i`                          | Cast vector of type `__m256d` to type `__m256i`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castpd128_pd256(a: __m128d): __m256d`                       | Cast vector of type `__m128d` to type `__m256d`; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castpd256_pd128(a: __m256d): __m128d`                       | Cast vector of type `__m256d` to type `__m128d`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castps_pd (a: __m256): __m256d`                             | Cast vector of type `__m256` to type `__m256d`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castps_si256 (a: __m256): __m256i`                          | Cast vector of type `__m256` to type `__m256i`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castps128_ps256 (a: __m128): __m256`                        | Cast vector of type `__m128` to type `__m256`; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |
| `_mm256_castps256_ps128 (a: __m256): __m128`                        | Cast vector of type `__m256` to type `__m128`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency. |




## `_mm256_add_pd(a: __m256d, b: __m256d): __m256d`

Add packed double precision (64-bit) floating point elements in a and b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_add_pd(__m256d a, __m256d b)
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vaddpd ymm, ymm, ymm |
| CPUID Flags | AVX                  |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := a[i+63:i] + b[i+63:i]
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |

## `_mm256_add_ps(a: __m256, b: __m256d): __m256d`

Add packed single precision (32 bit) floating point elements in a and b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_add_ps (__m256 a, __m256 b)
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vaddps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := a[i+31:i] + b[i+31:i]
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |

## `_mm256_addsub_pd(a: __m256d, b: __m256d): __m256d`

Alternatively add and subtract packed double precision (64 bit) floating point elements in a to/from elements in b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_addsub_pd (__m256d a, __m256d b)
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vaddsubpd ymm, ymm, ymm |
| CPUID Flags | AVX                     |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	IF ((j & 1) == 0)
		dst[i+63:i] := a[i+63:i] - b[i+63:i]
	ELSE
		dst[i+63:i] := a[i+63:i] + b[i+63:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |

## `_mm256_addsub_ps(a: __m256, b: __m256): __m256`

Alternatively add and subtract packed single precision (32 bit) floating point elements in a to/from packed elements in b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_addsub_ps (__m256 a, __m256 b)
```

| -           | Description             |
| ----------- | ----------------------- |
| Instruction | vaddsubps ymm, ymm, ymm |
| CPUID Flags | AVX                     |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	IF ((j & 1) == 0)
		dst[i+31:i] := a[i+31:i] - b[i+31:i]
	ELSE
		dst[i+31:i] := a[i+31:i] + b[i+31:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 4       | 0.5              |
| Skylake      | 4       | 0.5              |
| Broadwell    | 3       | 1                |
| Haswell      | 3       | 1                |
| Ivy Bridge   | 3       | 1                |

## `_mm256_and_pd(a: __m256d, b: __m256d): __m256d`

Compute the bitwise AND of packed double precision (64 bit) floating point elements in a and b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_and_pd (__m256d a, __m256d b)
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vandpd ymm, ymm, ymm |
| CPUID Flags | AVX                  |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := (a[i+63:i] AND b[i+63:i])
ENDFOR
dst[MAX:256] := 0
```
### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |

## `_mm256_and_ps(a: __m256, b: __m256): __m256`

Compute the bitwise AND of packed (32 bit) floating point elements in a and b, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_and_ps(__m256 a, __m256 b)
```

| -           | Description          |
| ----------- | -------------------- |
| Instruction | vandps ymm, ymm, ymm |
| CPUID Flags | AVX                  |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := (a[i+31:i] AND b[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |

## `_mm256_andnot_pd(a: __m256d, b: __m256d): __m256d`

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_andnot_pd (__m256d a, __m256d b)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vandnpd ymm, ymm, ymm |
| CPUID Flags | AVX                   |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := ((NOT a[i+63:i]) AND b[i+63:i])
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |


## `_mm256_andnot_ps(a: __m256, b: __m256): __m256`

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_andnot_ps (__m256 a, __m256 b)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vandnps ymm, ymm, ymm |
| CPUID Flags | AVX                   |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := ((NOT a[i+31:i]) AND b[i+31:i])
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 1                |
| Haswell      | 1       | 1                |
| Ivy Bridge   | 1       | 1                |

## `_mm256_blend_pd(a: __m256d, b: __m256d, imm8: const int): __m256d`

Blend packed double precision (64 bit) floating point elements from a and b using control mask imm8, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_blend_pd (__m256d a, __m256d b, const int imm8);
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendpd ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                          |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	IF imm8[j]
		dst[i+63:i] := b[i+63:i]
	ELSE
		dst[i+63:i] := a[i+63:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |
| Ivy Bridge   | 1       | 0.5              |

## `_mm256_blend_ps(a: __m256, b: __m256, const int imm8): __m256`

Blend packed single precision (32 bit) floating point elements from a and b using control mask imm8, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_blend_ps (__m256 a, __m256 b, const int imm8)
```

| -           | Description |
| ----------- | ----------- |
| Instruction | vblendps ymm, ymm, ymm, imm8 |
| CPUID Flags | AVX                          |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	IF imm8[j]
		dst[i+31:i] := b[i+31:i]
	ELSE
		dst[i+31:i] := a[i+31:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 1       | 0.33             |
| Skylake      | 1       | 0.33             |
| Broadwell    | 1       | 0.33             |
| Haswell      | 1       | 0.33             |
| Ivy Bridge   | 1       | 0.5              |

## `_mm256_blend_ps(a: __m256, b: __m256, const int imm8): __m256`

Blend packed double precision (64 bit) floating point elements from a and b using mask, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_blendv_pd (__m256d a, __m256d b, __m256d mask)
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendvpd ymm, ymm, ymm, ymm |
| CPUID Flags | AVX                          |

### __Operation__

```
FOR j := 0 to 3
	i := j*64
	IF mask[i+63]
		dst[i+63:i] := b[i+63:i]
	ELSE
		dst[i+63:i] := a[i+63:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 2       | 0.66             |
| Broadwell    | 2       | 2                |
| Haswell      | 2       | 2                |
| Ivy Bridge   | 1       | 1                |

## `_mm256_blendv_ps(a: __m256, b: __m256, mask: __m256): __m256`

Blend packed single precision (32 bit) floating point elements from a and b using mask, and store the results in destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_blendv_ps (__m256 a, __m256 b, __m256 mask)
```

| -           | Description                  |
| ----------- | ---------------------------- |
| Instruction | vblendvps ymm, ymm, ymm, ymm |
| CPUID Flags | AVX                          |

### __Operation__

```
FOR j := 0 to 7
	i := j*32
	IF mask[i+31]
		dst[i+31:i] := b[i+31:i]
	ELSE
		dst[i+31:i] := a[i+31:i]
	FI
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | -       | 1                |
| Skylake      | 2       | 0.66             |
| Broadwell    | 2       | 2                |
| Haswell      | 2       | 2                |
| Ivy Bridge   | 1       | 1                |

## `_mm256_broadcast_pd(mem_addr: __m128d const *): __m256d`

Broadcast 128 bits from memory (composed of 2 packed double precision (64 bit) floating point elements) to all elemenbts of destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_broadcast_pd (__m128d const * mem_addr)
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vbroadcastf128 ymm, m128 |
| CPUID Flags | AVX                      |

### __Operation__

```
tmp[127:0] := MEM[mem_addr+127:mem_addr]
dst[127:0] := tmp[127:0]
dst[255:128] := tmp[127:0]
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |

## `_mm256_broadcast_ps(mem_addr: __m128 const *): __m256`

Broadcast 128 bits from memory (composed of 4 packed single precision (32 bit) floating point elements) to all elements of destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_broadcast_ps (__m128 const * mem_addr)
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | vbroadcastf128 ymm, m128 |
| CPUID Flags | AVX                      |

### __Operation__

이것은 체크해보자. 원하는 것대로 동작하지 않을 것 같다. 127 이 아니라 64 일 듯 보인다.

```
tmp[127:0] := MEM[mem_addr+127:mem_addr]
dst[127:0] := tmp[127:0]
dst[255:128] := tmp[127:0]
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |

## `_mm256_broadcast_sd(mem_addr: double const *): __m256d`

Broadcast a double precision (64 bit) floating point element from memory to all elements of destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_broadcast_sd (double const * mem_addr)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastsd ymm, m64 |
| CPUID Flags | AVX                   |

### __Operation__

```
tmp[63:0] := MEM[mem_addr+63:mem_addr]
FOR j := 0 to 3
	i := j*64
	dst[i+63:i] := tmp[63:0]
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |

## `_mm_broadcast_ss(mem_addr: float const *): __m128`

Broadcast a single precision (32 bit) floating point element from memory to all elements of destination.

이것 역시 리턴 값을 확인해보자.

### __Synopsis__

```c
#include <immintrin.h>

__m128 _mm_broadcast_ss (float const * mem_addr)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastss xmm, m32 |
| CPUID Flags | AVX                   |

### __Operation__

```
tmp[31:0] := MEM[mem_addr+31:mem_addr]
FOR j := 0 to 3
	i := j*32
	dst[i+31:i] := tmp[31:0]
ENDFOR
dst[MAX:128] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 6       | 0.5              |
| Skylake      | 6       | 0.5              |

## `_mm256_broadcast_ss(mem_addr: float const *): __m256`

Broadcast a single precision (32 bit) floating point element from memory to all elements of destination.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_broadcast_ss (float const * mem_addr)
```

| -           | Description           |
| ----------- | --------------------- |
| Instruction | vbroadcastss ymm, m32 |
| CPUID Flags | AVX                   |

### __Operation__

```
tmp[31:0] := MEM[mem_addr+31:mem_addr]
FOR j := 0 to 7
	i := j*32
	dst[i+31:i] := tmp[31:0]
ENDFOR
dst[MAX:256] := 0
```

### __Performance__

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Icelake      | 7       | 0.5              |
| Skylake      | 7       | 0.5              |

## `_mm256_castpd_ps(a: __m256d): __m256`

Cast vector of type `__m256d` to type `__m256`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_castpd_ps (__m256d a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castpd_si256(a: __m256d): __m256i`

Cast vector of type `__m256d` to type `__m256i`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256i _mm256_castpd_si256 (__m256d a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castpd128_pd256(a: __m128d): __m256d`

Cast vector of type `__m128d` to type `__m256d`; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_castpd128_pd256 (__m128d a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

### __Synopsis__

```c
#include <immintrin.h>

__m128d _mm256_castpd256_pd128 (__m256d a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castps_pd (a: __m256): __m256d`

Cast vector of type `__m256` to type `__m256d`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_castps_pd (__m256 a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castps_si256 (a: __m256): __m256i`

Cast vector of type `__m256` to type `__m256i`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256i _mm256_castps_si256 (__m256 a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castps128_ps256 (a: __m128): __m256`

Cast vector of type `__m128` to type `__m256`; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_castps128_ps256 (__m128 a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castps256_ps128 (a: __m256): __m128` 

Cast vector of type `__m256` to type `__m128`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m128 _mm256_castps256_ps128 (__m256 a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castsi128_si256 (a: __m128i): __m256i`

Cast vector of type `__m128i` to type `__m256i`; the upper 128 bits of the result are undefined. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256i _mm256_castsi128_si256 (__m128i a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castsi256_pd (a: __m256i): __m256d`

Cast vector of type __m256i to type __m256d. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256d _mm256_castsi256_pd (__m256i a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castsi256_ps (a: __m256i): __m256`

Cast vector of type `__m256i` to type `__m256`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m256 _mm256_castsi256_ps (__m256i a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |

## `_mm256_castsi256_si128 (a: __m256i): __m128i`

Cast vector of type `__m256i` to type `__m128i`. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.

### __Synopsis__

```c
#include <immintrin.h>

__m128i _mm256_castsi256_si128 (__m256i a)
```

| -           | Description |
| ----------- | ----------- |
| CPUID Flags | AVX         |
