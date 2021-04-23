`_mm_cmpestra(x: __m128i, int xlen, y: __m128i, ylen, imm8: int): int`
======================================================================

> Compare packed strings in x and y with lengths length x and length y using the control in imm8, and returns 1 if y did not contain a null character and the resulting mask was zero, and 0 otherwise. 

imm can be a combination of:

| Mask                           | Description                              |
| ------------------------------ | ---------------------------------------- |
| _SIDD_UBYTE_OPS                | unsigned 8-bit characters                |
| _SIDD_UWORD_OPS                | unsigned 16-bit characters               |
| _SIDD_SBYTE_OPS                | signed 8-bit characters                  |
| _SIDD_SWORD_OPS                | signed 16-bit characters                 |
| _SIDD_CMP_EQUAL_ANY            | compare equal any                        |
| _SIDD_CMP_RANGES               | compare ranges                           |
| _SIDD_CMP_EQUAL_EACH           | compare equal each                       |
| _SIDD_CMP_EQUAL_ORDERED        | compare equal ordered                    |
| _SIDD_NEGATIVE_POLARITY        | negate results                           |
| _SIDD_MASKED_NEGATIVE_POLARITY | negate results only before end of string |
| _SIDD_LEAST_SIGNIFICANT        | index only: return last significant bit  |
| _SIDD_MOST_SIGNIFICANT         | index only: return most significant bit  |
| _SIDD_BIT_MASK                 | mask only: return bit mask               |
| _SIDD_UNIT_MASK                | mask only: return byte/word mask         |

## Synopsis

```c
#include <nmmintrin.h>

int _mm_cmpestra (__m128i a, int la, __m128i b, int lb, const int imm8);
```

| -           | Description              |
| ----------- | ------------------------ |
| Instruction | pcmpestri xmm, xmm, imm8 |
| CPUID Flags | SSE4.2                   |

## Operation

```
size := (imm8[0] ? 16 : 8) // 8 or 16-bit characters
UpperBound := (128 / size) - 1
BoolRes := 0
// compare all characters
aInvalid := 0
bInvalid := 0
FOR i := 0 to UpperBound
	m := i*size
	FOR j := 0 to UpperBound
		n := j*size
		BoolRes.word[i].bit[j] := (a[m+size-1:m] == b[n+size-1:n]) ? 1 : 0
		
		// invalidate characters after EOS
		IF i == la
			aInvalid := 1
		FI
		IF j == lb
			bInvalid := 1
		FI
		
		// override comparisons for invalid characters
		CASE (imm8[3:2]) OF
		0:  // equal any
			IF (!aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && !bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			FI
		1:  // ranges
			IF (!aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && !bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			FI
		2:  // equal each
			IF (!aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && !bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 1
			FI
		3:  // equal ordered
			IF (!aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 0
			ELSE IF (aInvalid && !bInvalid)
				BoolRes.word[i].bit[j] := 1
			ELSE IF (aInvalid && bInvalid)
				BoolRes.word[i].bit[j] := 1
			FI
		ESAC
	ENDFOR
ENDFOR
// aggregate results
CASE (imm8[3:2]) OF
0:  // equal any
	IntRes1 := 0
	FOR i := 0 to UpperBound
		FOR j := 0 to UpperBound
			IntRes1[i] := IntRes1[i] OR BoolRes.word[i].bit[j]
		ENDFOR
	ENDFOR
1:  // ranges
	IntRes1 := 0
	FOR i := 0 to UpperBound
		FOR j := 0 to UpperBound
			IntRes1[i] := IntRes1[i] OR (BoolRes.word[i].bit[j] AND BoolRes.word[i].bit[j+1])
			j += 2
		ENDFOR
	ENDFOR
2:  // equal each
	IntRes1 := 0
	FOR i := 0 to UpperBound
		IntRes1[i] := BoolRes.word[i].bit[i]
	ENDFOR
3:  // equal ordered
	IntRes1 := (imm8[0] ? 0xFF : 0xFFFF)
	FOR i := 0 to UpperBound
		k := i
		FOR j := 0 to UpperBound-i
			IntRes1[i] := IntRes1[i] AND BoolRes.word[k].bit[j]
			k := k+1
		ENDFOR
	ENDFOR
ESAC
// optionally negate results
FOR i := 0 to UpperBound
	IF imm8[4]
		IF imm8[5] // only negate valid
			IF i >= lb // invalid, don't negate
				IntRes2[i] := IntRes1[i]
			ELSE // valid, negate
				IntRes2[i] := -1 XOR IntRes1[i]
			FI
		ELSE // negate all
			IntRes2[i] := -1 XOR IntRes1[i]
		FI
	ELSE // don't negate
		IntRes2[i] := IntRes1[i]
	FI
ENDFOR
// output
dst := (IntRes2 == 0) AND (lb > UpperBound)
```

## Performance

| Architecture | Latency | Throughput (CPI) |
| ------------ | ------- | ---------------- |
| Skylake      | 18      | 4                |
