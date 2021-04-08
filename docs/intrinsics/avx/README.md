# AVX

| FUNCTION                                         | DESCRIPTION |
| ------------------------------------------------ | ----------- |
| `_mm256_add_pd(a: __m256d, b: __m256d): __m256d` | Add packed double precision (64 bit) floating point elements in a and b, and store the results in destination. |



vaddps
__m256 _mm256_add_ps (__m256 a, __m256 b)
vaddsubpd
__m256d _mm256_addsub_pd (__m256d a, __m256d b)
vaddsubps
__m256 _mm256_addsub_ps (__m256 a, __m256 b)
vandpd
__m256d _mm256_and_pd (__m256d a, __m256d b)
vandps
__m256 _mm256_and_ps (__m256 a, __m256 b)
vandnpd
__m256d _mm256_andnot_pd (__m256d a, __m256d b)
vandnps
__m256 _mm256_andnot_ps (__m256 a, __m256 b)
vblendpd
__m256d _mm256_blend_pd (__m256d a, __m256d b, const int imm8)
vblendps
__m256 _mm256_blend_ps (__m256 a, __m256 b, const int imm8)
vblendvpd
__m256d _mm256_blendv_pd (__m256d a, __m256d b, __m256d mask)
vblendvps
__m256 _mm256_blendv_ps (__m256 a, __m256 b, __m256 mask)
vbroadcastf128
__m256d _mm256_broadcast_pd (__m128d const * mem_addr)
vbroadcastf128
__m256 _mm256_broadcast_ps (__m128 const * mem_addr)
vbroadcastsd
__m256d _mm256_broadcast_sd (double const * mem_addr)
vbroadcastss
__m128 _mm_broadcast_ss (float const * mem_addr)
vbroadcastss
__m256 _mm256_broadcast_ss (float const * mem_addr)
__m256 _mm256_castpd_ps (__m256d a)
__m256i _mm256_castpd_si256 (__m256d a)
__m256d _mm256_castpd128_pd256 (__m128d a)
__m128d _mm256_castpd256_pd128 (__m256d a)
__m256d _mm256_castps_pd (__m256 a)
__m256i _mm256_castps_si256 (__m256 a)
__m256 _mm256_castps128_ps256 (__m128 a)
__m128 _mm256_castps256_ps128 (__m256 a)
__m256i _mm256_castsi128_si256 (__m128i a)
__m256d _mm256_castsi256_pd (__m256i a)
__m256 _mm256_castsi256_ps (__m256i a)
__m128i _mm256_castsi256_si128 (__m256i a)
vroundpd
__m256d _mm256_ceil_pd (__m256d a)
vroundps
__m256 _mm256_ceil_ps (__m256 a)
vcmppd
__m128d _mm_cmp_pd (__m128d a, __m128d b, const int imm8)
vcmppd
__m256d _mm256_cmp_pd (__m256d a, __m256d b, const int imm8)
vcmpps
__m128 _mm_cmp_ps (__m128 a, __m128 b, const int imm8)
vcmpps
__m256 _mm256_cmp_ps (__m256 a, __m256 b, const int imm8)
vcmpsd
__m128d _mm_cmp_sd (__m128d a, __m128d b, const int imm8)
vcmpss
__m128 _mm_cmp_ss (__m128 a, __m128 b, const int imm8)
vcvtdq2pd
__m256d _mm256_cvtepi32_pd (__m128i a)
vcvtdq2ps
__m256 _mm256_cvtepi32_ps (__m256i a)
vcvtpd2dq
__m128i _mm256_cvtpd_epi32 (__m256d a)
vcvtpd2ps
__m128 _mm256_cvtpd_ps (__m256d a)
vcvtps2dq
__m256i _mm256_cvtps_epi32 (__m256 a)
vcvtps2pd
__m256d _mm256_cvtps_pd (__m128 a)
vmovsd
double _mm256_cvtsd_f64 (__m256d a)
vmovd
int _mm256_cvtsi256_si32 (__m256i a)
vmovss
float _mm256_cvtss_f32 (__m256 a)
vcvttpd2dq
__m128i _mm256_cvttpd_epi32 (__m256d a)
vcvttps2dq
__m256i _mm256_cvttps_epi32 (__m256 a)
vdivpd
__m256d _mm256_div_pd (__m256d a, __m256d b)
vdivps
__m256 _mm256_div_ps (__m256 a, __m256 b)
vdpps
__m256 _mm256_dp_ps (__m256 a, __m256 b, const int imm8)
...
__int32 _mm256_extract_epi32 (__m256i a, const int index)
...
__int64 _mm256_extract_epi64 (__m256i a, const int index)
vextractf128
__m128d _mm256_extractf128_pd (__m256d a, const int imm8)
vextractf128
__m128 _mm256_extractf128_ps (__m256 a, const int imm8)
vextractf128
__m128i _mm256_extractf128_si256 (__m256i a, const int imm8)
vroundpd
__m256d _mm256_floor_pd (__m256d a)
vroundps
__m256 _mm256_floor_ps (__m256 a)
vhaddpd
__m256d _mm256_hadd_pd (__m256d a, __m256d b)
vhaddps
__m256 _mm256_hadd_ps (__m256 a, __m256 b)
vhsubpd
__m256d _mm256_hsub_pd (__m256d a, __m256d b)
vhsubps
__m256 _mm256_hsub_ps (__m256 a, __m256 b)
...
__m256i _mm256_insert_epi16 (__m256i a, __int16 i, const int index)
...
__m256i _mm256_insert_epi32 (__m256i a, __int32 i, const int index)
...
__m256i _mm256_insert_epi64 (__m256i a, __int64 i, const int index)
...
__m256i _mm256_insert_epi8 (__m256i a, __int8 i, const int index)
vinsertf128
__m256d _mm256_insertf128_pd (__m256d a, __m128d b, int imm8)
vinsertf128
__m256 _mm256_insertf128_ps (__m256 a, __m128 b, int imm8)
vinsertf128
__m256i _mm256_insertf128_si256 (__m256i a, __m128i b, int imm8)
vlddqu
__m256i _mm256_lddqu_si256 (__m256i const * mem_addr)
vmovapd
__m256d _mm256_load_pd (double const * mem_addr)
vmovaps
__m256 _mm256_load_ps (float const * mem_addr)
vmovdqa
__m256i _mm256_load_si256 (__m256i const * mem_addr)
vmovupd
__m256d _mm256_loadu_pd (double const * mem_addr)
vmovups
__m256 _mm256_loadu_ps (float const * mem_addr)
vmovdqu
__m256i _mm256_loadu_si256 (__m256i const * mem_addr)
...
__m256 _mm256_loadu2_m128 (float const* hiaddr, float const* loaddr)
...
__m256d _mm256_loadu2_m128d (double const* hiaddr, double const* loaddr)
...
__m256i _mm256_loadu2_m128i (__m128i const* hiaddr, __m128i const* loaddr)
vmaskmovpd
__m128d _mm_maskload_pd (double const * mem_addr, __m128i mask)
vmaskmovpd
__m256d _mm256_maskload_pd (double const * mem_addr, __m256i mask)
vmaskmovps
__m128 _mm_maskload_ps (float const * mem_addr, __m128i mask)
vmaskmovps
__m256 _mm256_maskload_ps (float const * mem_addr, __m256i mask)
vmaskmovpd
void _mm_maskstore_pd (double * mem_addr, __m128i mask, __m128d a)
vmaskmovpd
void _mm256_maskstore_pd (double * mem_addr, __m256i mask, __m256d a)
vmaskmovps
void _mm_maskstore_ps (float * mem_addr, __m128i mask, __m128 a)
vmaskmovps
void _mm256_maskstore_ps (float * mem_addr, __m256i mask, __m256 a)
vmaxpd
__m256d _mm256_max_pd (__m256d a, __m256d b)
vmaxps
__m256 _mm256_max_ps (__m256 a, __m256 b)
vminpd
__m256d _mm256_min_pd (__m256d a, __m256d b)
vminps
__m256 _mm256_min_ps (__m256 a, __m256 b)
vmovddup
__m256d _mm256_movedup_pd (__m256d a)
vmovshdup
__m256 _mm256_movehdup_ps (__m256 a)
vmovsldup
__m256 _mm256_moveldup_ps (__m256 a)
vmovmskpd
int _mm256_movemask_pd (__m256d a)
vmovmskps
int _mm256_movemask_ps (__m256 a)
vmulpd
__m256d _mm256_mul_pd (__m256d a, __m256d b)
vmulps
__m256 _mm256_mul_ps (__m256 a, __m256 b)
vorpd
__m256d _mm256_or_pd (__m256d a, __m256d b)
vorps
__m256 _mm256_or_ps (__m256 a, __m256 b)
vpermilpd
__m128d _mm_permute_pd (__m128d a, int imm8)
vpermilpd
__m256d _mm256_permute_pd (__m256d a, int imm8)
vpermilps
__m128 _mm_permute_ps (__m128 a, int imm8)
vpermilps
__m256 _mm256_permute_ps (__m256 a, int imm8)
vperm2f128
__m256d _mm256_permute2f128_pd (__m256d a, __m256d b, int imm8)
vperm2f128
__m256 _mm256_permute2f128_ps (__m256 a, __m256 b, int imm8)
vperm2f128
__m256i _mm256_permute2f128_si256 (__m256i a, __m256i b, int imm8)
vpermilpd
__m128d _mm_permutevar_pd (__m128d a, __m128i b)
vpermilpd
__m256d _mm256_permutevar_pd (__m256d a, __m256i b)
vpermilps
__m128 _mm_permutevar_ps (__m128 a, __m128i b)
vpermilps
__m256 _mm256_permutevar_ps (__m256 a, __m256i b)
vrcpps
__m256 _mm256_rcp_ps (__m256 a)
vroundpd
__m256d _mm256_round_pd (__m256d a, int rounding)
vroundps
__m256 _mm256_round_ps (__m256 a, int rounding)
vrsqrtps
__m256 _mm256_rsqrt_ps (__m256 a)
...
__m256i _mm256_set_epi16 (short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8, short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0)
...
__m256i _mm256_set_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0)
...
__m256i _mm256_set_epi64x (__int64 e3, __int64 e2, __int64 e1, __int64 e0)
...
__m256i _mm256_set_epi8 (char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24, char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16, char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8, char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0)
vinsertf128
__m256 _mm256_set_m128 (__m128 hi, __m128 lo)
vinsertf128
__m256d _mm256_set_m128d (__m128d hi, __m128d lo)
vinsertf128
__m256i _mm256_set_m128i (__m128i hi, __m128i lo)
...
__m256d _mm256_set_pd (double e3, double e2, double e1, double e0)
...
__m256 _mm256_set_ps (float e7, float e6, float e5, float e4, float e3, float e2, float e1, float e0)
...
__m256i _mm256_set1_epi16 (short a)
...
__m256i _mm256_set1_epi32 (int a)
...
__m256i _mm256_set1_epi64x (long long a)
...
__m256i _mm256_set1_epi8 (char a)
...
__m256d _mm256_set1_pd (double a)
...
__m256 _mm256_set1_ps (float a)
...
__m256i _mm256_setr_epi16 (short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8, short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0)
...
__m256i _mm256_setr_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0)
...
__m256i _mm256_setr_epi64x (__int64 e3, __int64 e2, __int64 e1, __int64 e0)
...
__m256i _mm256_setr_epi8 (char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24, char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16, char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8, char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0)
vinsertf128
__m256 _mm256_setr_m128 (__m128 lo, __m128 hi)
vinsertf128
__m256d _mm256_setr_m128d (__m128d lo, __m128d hi)
vinsertf128
__m256i _mm256_setr_m128i (__m128i lo, __m128i hi)
...
__m256d _mm256_setr_pd (double e3, double e2, double e1, double e0)
...
__m256 _mm256_setr_ps (float e7, float e6, float e5, float e4, float e3, float e2, float e1, float e0)
vxorpd
__m256d _mm256_setzero_pd (void)
vxorps
__m256 _mm256_setzero_ps (void)
vpxor
__m256i _mm256_setzero_si256 (void)
vshufpd
__m256d _mm256_shuffle_pd (__m256d a, __m256d b, const int imm8)
vshufps
__m256 _mm256_shuffle_ps (__m256 a, __m256 b, const int imm8)
vsqrtpd
__m256d _mm256_sqrt_pd (__m256d a)
vsqrtps
__m256 _mm256_sqrt_ps (__m256 a)
vmovapd
void _mm256_store_pd (double * mem_addr, __m256d a)
vmovaps
void _mm256_store_ps (float * mem_addr, __m256 a)
vmovdqa
void _mm256_store_si256 (__m256i * mem_addr, __m256i a)
vmovupd
void _mm256_storeu_pd (double * mem_addr, __m256d a)
vmovups
void _mm256_storeu_ps (float * mem_addr, __m256 a)
vmovdqu
void _mm256_storeu_si256 (__m256i * mem_addr, __m256i a)
...
void _mm256_storeu2_m128 (float* hiaddr, float* loaddr, __m256 a)
...
void _mm256_storeu2_m128d (double* hiaddr, double* loaddr, __m256d a)
...
void _mm256_storeu2_m128i (__m128i* hiaddr, __m128i* loaddr, __m256i a)
vmovntpd
void _mm256_stream_pd (double * mem_addr, __m256d a)
vmovntps
void _mm256_stream_ps (float * mem_addr, __m256 a)
vmovntdq
void _mm256_stream_si256 (__m256i * mem_addr, __m256i a)
vsubpd
__m256d _mm256_sub_pd (__m256d a, __m256d b)
vsubps
__m256 _mm256_sub_ps (__m256 a, __m256 b)
vtestpd
int _mm_testc_pd (__m128d a, __m128d b)
vtestpd
int _mm256_testc_pd (__m256d a, __m256d b)
vtestps
int _mm_testc_ps (__m128 a, __m128 b)
vtestps
int _mm256_testc_ps (__m256 a, __m256 b)
vptest
int _mm256_testc_si256 (__m256i a, __m256i b)
vtestpd
int _mm_testnzc_pd (__m128d a, __m128d b)
vtestpd
int _mm256_testnzc_pd (__m256d a, __m256d b)
vtestps
int _mm_testnzc_ps (__m128 a, __m128 b)
vtestps
int _mm256_testnzc_ps (__m256 a, __m256 b)
vptest
int _mm256_testnzc_si256 (__m256i a, __m256i b)
vtestpd
int _mm_testz_pd (__m128d a, __m128d b)
vtestpd
int _mm256_testz_pd (__m256d a, __m256d b)
vtestps
int _mm_testz_ps (__m128 a, __m128 b)
vtestps
int _mm256_testz_ps (__m256 a, __m256 b)
vptest
int _mm256_testz_si256 (__m256i a, __m256i b)
__m256d _mm256_undefined_pd (void)
__m256 _mm256_undefined_ps (void)
__m256i _mm256_undefined_si256 (void)
vunpckhpd
__m256d _mm256_unpackhi_pd (__m256d a, __m256d b)
vunpckhps
__m256 _mm256_unpackhi_ps (__m256 a, __m256 b)
vunpcklpd
__m256d _mm256_unpacklo_pd (__m256d a, __m256d b)
vunpcklps
__m256 _mm256_unpacklo_ps (__m256 a, __m256 b)
vxorpd
__m256d _mm256_xor_pd (__m256d a, __m256d b)
vxorps
__m256 _mm256_xor_ps (__m256 a, __m256 b)
vzeroall
void _mm256_zeroall (void)
vzeroupper
void _mm256_zeroupper (void)
__m256d _mm256_zextpd128_pd256 (__m128d a)
__m256 _mm256_zextps128_ps256 (__m128 a)
__m256i _mm256_zextsi128_si256 (__m128i a)


https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX&expand=124