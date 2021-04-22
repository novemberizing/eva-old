## AVX(Advanced Vector Extension) - Intel Intrinsics

> https://software.intel.com/sites/landingpage/IntrinsicsGuide/

__Compile__

```
gcc -mavx2 [filename]
```

| Function | Description | Example |
| -------- | ----------- | ------- |
| [_mm256_abs_epi16](_mm256_abs_epi16.md) | abs | [_mm256_abs_epi16.c](../../../src/example/avx/_mm256_abs_epi16.c) |
| [_mm256_abs_epi32](_mm256_abs_epi32.md) | abs | [_mm256_abs_epi32.c](../../../src/example/avx/_mm256_abs_epi32.c) |
| [_mm256_abs_epi8](_mm256_abs_epi8.md) | abs | [_mm256_abs_epi8.c](../../../src/example/avx/_mm256_abs_epi8.c) |
| [_mm256_add_epi16](_mm256_add_epi16.md) | add | [_mm256_add_epi16.c](../../../src/example/avx/_mm256_add_epi16.c) |
| [_mm256_add_epi32](_mm256_add_epi32.md) | add | [_mm256_add_epi32.c](../../../src/example/avx/_mm256_add_epi32.c) |
| [_mm256_add_epi64](_mm256_add_epi64.md) | add | [_mm256_add_epi64.c](../../../src/example/avx/_mm256_add_epi64.c) |
| [_mm256_add_epi8](_mm256_add_epi8.md) | add | [_mm256_add_epi8.c](../../../src/example/avx/_mm256_add_epi8.c) |
| [_mm256_add_pd](_mm256_add_pd.md) | add | [_mm256_add_pd.c](../../../src/example/avx/_mm256_add_pd.c) |
| [_mm256_add_ps](_mm256_add_ps.md) | add | [_mm256_add_ps.c](../../../src/example/avx/_mm256_add_ps.c) |
| [_mm256_adds_epi16](_mm256_adds_epi16.md) | add saturation | [_mm256_adds_epi16.c](../../../src/example/avx/_mm256_adds_epi16.c) |
| [_mm256_adds_epi8](_mm256_adds_epi8.md) | add saturation | [_mm256_adds_epi8.c](../../../src/example/avx/_mm256_adds_epi8.c) |
| [_mm256_adds_epu16](_mm256_adds_epu16.md) | add saturation | [_mm256_adds_epu16.c](../../../src/example/avx/_mm256_adds_epu16.c) |
| [_mm256_adds_epu8](_mm256_adds_epu8.md) | add saturation | [_mm256_adds_epu8.c](../../../src/example/avx/_mm256_adds_epu8.c) |
| [_mm256_addsub_pd](_mm256_addsub_pd.md) | add & sub | [_mm256_addsub_pd.c](../../../src/example/avx/_mm256_addsub_pd.c) |
| [_mm256_addsub_ps](_mm256_addsub_ps.md) | add & sub | [_mm256_addsub_ps.c](../../../src/example/avx/_mm256_addsub_ps.c) |
| [_mm256_alignr_epi8](_mm256_alignr_epi8.md) | align right | [_mm256_alignr_epi8.c](../../../src/example/avx/_mm256_alignr_epi8.c) |
| [_mm256_andnot_pd](_mm256_andnot_pd.md) | and not | [_mm256_andnot_pd.c](../../../src/example/avx/_mm256_andnot_pd.c) |
| [_mm256_andnot_ps](_mm256_andnot_ps.md) | and not | [_mm256_andnot_ps.c](../../../src/example/avx/_mm256_andnot_ps.c) |
| [_mm256_andnot_si256](_mm256_andnot_si256.md) | and not | [_mm256_andnot_si256.c](../../../src/example/avx/_mm256_andnot_si256.c) |
| [_mm256_and_pd](_mm256_and_pd.md) | and | [_mm256_and_pd.c](../../../src/example/avx/_mm256_and_pd.c) |
| [_mm256_and_ps](_mm256_and_ps.md) | and | [_mm256_and_ps.c](../../../src/example/avx/_mm256_and_ps.c) |
| [_mm256_and_si256](_mm256_and_si256.md) | and | [_mm256_and_si256.c](../../../src/example/avx/_mm256_and_si256.c) |
| [_mm256_avg_epu16](_mm256_avg_epu16.md) | average | [_mm256_avg_epu16.c](../../../src/example/avx/_mm256_avg_epu16.c) |
| [_mm256_avg_epu8](_mm256_avg_epu8.md) | average | [_mm256_avg_epu8.c](../../../src/example/avx/_mm256_avg_epu8.c) |
| [_mm256_blend_epi16](_mm256_blend_epi16.md) | blend | [_mm256_blend_epi16.c](../../../src/example/avx/_mm256_blend_epi16.c) |
| [_mm256_blend_epi32](_mm256_blend_epi32.md) | blend | [_mm256_blend_epi32.c](../../../src/example/avx/_mm256_blend_epi32.c) |
| [_mm256_blend_pd](_mm256_blend_pd.md) | blend | [_mm256_blend_pd.c](../../../src/example/avx/_mm256_blend_pd.c) |
| [_mm256_blend_ps](_mm256_blend_ps.md) | blend | [_mm256_blend_ps.c](../../../src/example/avx/_mm256_blend_ps.c) |
| [_mm256_blendv_epi8](_mm256_blendv_epi8.md) | blend | [_mm256_blendv_epi8.c](../../../src/example/avx/_mm256_blendv_epi8.c) |
| [_mm256_blendv_pd](_mm256_blendv_pd.md) | blend | [_mm256_blendv_pd.c](../../../src/example/avx/_mm256_blendv_pd.c) |
| [_mm256_blendv_ps](_mm256_blendv_ps.md) | blend | [_mm256_blendv_ps.c](../../../src/example/avx/_mm256_blendv_ps.c) |
| [_mm256_broadcastb_epi8](_mm256_broadcastb_epi8.md) | broadcast | [_mm256_broadcastb_epi8.c](../../../src/example/avx/_mm256_broadcastb_epi8.c) |
| [_mm256_broadcastd_epi32](_mm256_broadcastd_epi32.md) | broadcast | [_mm256_broadcastd_epi32.c](../../../src/example/avx/_mm256_broadcastd_epi32.c) |
| [_mm256_broadcast_pd](_mm256_broadcast_pd.md) | broadcast | [_mm256_broadcast_pd.c](../../../src/example/avx/_mm256_broadcast_pd.c) |
| [_mm256_broadcast_ps](_mm256_broadcast_ps.md) | broadcast | [_mm256_broadcast_ps.c](../../../src/example/avx/_mm256_broadcast_ps.c) |
| [_mm256_broadcastq_epi64](_mm256_broadcastq_epi64.md) | broadcast | [_mm256_broadcastq_epi64.c](../../../src/example/avx/_mm256_broadcastq_epi64.c) |
| [_mm256_broadcast_sd](_mm256_broadcast_sd.md) | broadcast | [_mm256_broadcast_sd.c](../../../src/example/avx/_mm256_broadcast_sd.c) |
| [_mm256_broadcastsd_pd](_mm256_broadcastsd_pd.md) | broadcast | [_mm256_broadcastsd_pd.c](../../../src/example/avx/_mm256_broadcastsd_pd.c) |
| [_mm256_broadcastsi128_si256](_mm256_broadcastsi128_si256.md) | broadcast | [_mm256_broadcastsi128_si256.c](../../../src/example/avx/_mm256_broadcastsi128_si256.c) |
| [_mm256_broadcast_ss](_mm256_broadcast_ss.md) | broadcast | [_mm256_broadcast_ss.c](../../../src/example/avx/_mm256_broadcast_ss.c) |
| [_mm256_broadcastss_ps](_mm256_broadcastss_ps.md) | broadcast | [_mm256_broadcastss_ps.c](../../../src/example/avx/_mm256_broadcastss_ps.c) |
| [_mm256_broadcastw_epi16](_mm256_broadcastw_epi16.md) | broadcast | [_mm256_broadcastw_epi16.c](../../../src/example/avx/_mm256_broadcastw_epi16.c) |
| [_mm256_bslli_epi128](_mm256_bslli_epi128.md) | shift left | [_mm256_bslli_epi128.c](../../../src/example/avx/_mm256_bslli_epi128.c) |
| [_mm256_bsrli_epi128](_mm256_bsrli_epi128.md) | shift left | [_mm256_bsrli_epi128.c](../../../src/example/avx/_mm256_bsrli_epi128.c) |
| [_mm256_castpd128_pd256](_mm256_castpd128_pd256.md) | cast | [_mm256_castpd128_pd256.c](../../../src/example/avx/_mm256_castpd128_pd256.c) |
| [_mm256_castpd256_pd128](_mm256_castpd256_pd128.md) | cast | [_mm256_castpd256_pd128.c](../../../src/example/avx/_mm256_castpd256_pd128.c) |
| [_mm256_castpd_ps](_mm256_castpd_ps.md) | cast | [_mm256_castpd_ps.c](../../../src/example/avx/_mm256_castpd_ps.c) |
| [_mm256_castpd_si256](_mm256_castpd_si256.md) | cast | [_mm256_castpd_si256.c](../../../src/example/avx/_mm256_castpd_si256.c) |
| [_mm256_castps128_ps256](_mm256_castps128_ps256.md) | cast | [_mm256_castps128_ps256.c](../../../src/example/avx/_mm256_castps128_ps256.c) |
| [_mm256_castps256_ps128](_mm256_castps256_ps128.md) | cast | [_mm256_castps256_ps128.c](../../../src/example/avx/_mm256_castps256_ps128.c) |
| [_mm256_castps_pd](_mm256_castps_pd.md) | cast | [_mm256_castps_pd.c](../../../src/example/avx/_mm256_castps_pd.c) |
| [_mm256_castps_si256](_mm256_castps_si256.md) | cast | [_mm256_castps_si256.c](../../../src/example/avx/_mm256_castps_si256.c) |
| [_mm256_castsi128_si256](_mm256_castsi128_si256.md) | cast | [_mm256_castsi128_si256.c](../../../src/example/avx/_mm256_castsi128_si256.c) |
| [_mm256_castsi256_pd](_mm256_castsi256_pd.md) | cast | [_mm256_castsi256_pd.c](../../../src/example/avx/_mm256_castsi256_pd.c) |
| [_mm256_castsi256_ps](_mm256_castsi256_ps.md) | cast | [_mm256_castsi256_ps.c](../../../src/example/avx/_mm256_castsi256_ps.c) |
| [_mm256_castsi256_si128](_mm256_castsi256_si128.md) | cast | [_mm256_castsi256_si128.c](../../../src/example/avx/_mm256_castsi256_si128.c) |
| [_mm256_ceil_pd](_mm256_ceil_pd.md) | ceil | [_mm256_ceil_pd.c](../../../src/example/avx/_mm256_ceil_pd.c) |
| [_mm256_ceil_ps](_mm256_ceil_ps.md) | ceil | [_mm256_ceil_ps.c](../../../src/example/avx/_mm256_ceil_ps.c) |
| [_mm256_cmpeq_epi16](_mm256_cmpeq_epi16.md) | compare equal | [_mm256_cmpeq_epi16.c](../../../src/example/avx/_mm256_cmpeq_epi16.c) |
| [_mm256_cmpeq_epi32](_mm256_cmpeq_epi32.md) | compare equal | [_mm256_cmpeq_epi32.c](../../../src/example/avx/_mm256_cmpeq_epi32.c) |
| [_mm256_cmpeq_epi64](_mm256_cmpeq_epi64.md) | compare equal | [_mm256_cmpeq_epi64.c](../../../src/example/avx/_mm256_cmpeq_epi64.c) |
| [_mm256_cmpeq_epi8](_mm256_cmpeq_epi8.md) | compare equal | [_mm256_cmpeq_epi8.c](../../../src/example/avx/_mm256_cmpeq_epi8.c) |
| [_mm256_cmpgt_epi16](_mm256_cmpgt_epi16.md) | compare greater than | [_mm256_cmpgt_epi16.c](../../../src/example/avx/_mm256_cmpgt_epi16.c) |
| [_mm256_cmpgt_epi32](_mm256_cmpgt_epi32.md) | compare greater than | [_mm256_cmpgt_epi32.c](../../../src/example/avx/_mm256_cmpgt_epi32.c) |
| [_mm256_cmpgt_epi64](_mm256_cmpgt_epi64.md) | compare greater than | [_mm256_cmpgt_epi64.c](../../../src/example/avx/_mm256_cmpgt_epi64.c) |
| [_mm256_cmpgt_epi8](_mm256_cmpgt_epi8.md) | compare greater than | [_mm256_cmpgt_epi8.c](../../../src/example/avx/_mm256_cmpgt_epi8.c) |
| [_mm256_cmp_pd](_mm256_cmp_pd.md) | compare | [_mm256_cmp_pd.c](../../../src/example/avx/_mm256_cmp_pd.c) |
| [_mm256_cmp_ps](_mm256_cmp_ps.md) | compare | [_mm256_cmp_ps.c](../../../src/example/avx/_mm256_cmp_ps.c) |
| [_mm256_cvtepi16_epi32](_mm256_cvtepi16_epi32.md) | convert | [_mm256_cvtepi16_epi32.c](../../../src/example/avx/_mm256_cvtepi16_epi32.c) |
| [_mm256_cvtepi16_epi64](_mm256_cvtepi16_epi64.md) | convert | [_mm256_cvtepi16_epi64.c](../../../src/example/avx/_mm256_cvtepi16_epi64.c) |
| [_mm256_cvtepi32_epi64](_mm256_cvtepi32_epi64.md) | convert | [_mm256_cvtepi32_epi64.c](../../../src/example/avx/_mm256_cvtepi32_epi64.c) |
| [_mm256_cvtepi32_pd](_mm256_cvtepi32_pd.md) | convert | [_mm256_cvtepi32_pd.c](../../../src/example/avx/_mm256_cvtepi32_pd.c) |
| [_mm256_cvtepi32_ps](_mm256_cvtepi32_ps.md) | convert | [_mm256_cvtepi32_ps.c](../../../src/example/avx/_mm256_cvtepi32_ps.c) |
| [_mm256_cvtepi8_epi16](_mm256_cvtepi8_epi16.md) | convert | [_mm256_cvtepi8_epi16.c](../../../src/example/avx/_mm256_cvtepi8_epi16.c) |
| [_mm256_cvtepi8_epi32](_mm256_cvtepi8_epi32.md) | convert | [_mm256_cvtepi8_epi32.c](../../../src/example/avx/_mm256_cvtepi8_epi32.c) |
| [_mm256_cvtepi8_epi64](_mm256_cvtepi8_epi64.md) | convert | [_mm256_cvtepi8_epi64.c](../../../src/example/avx/_mm256_cvtepi8_epi64.c) |
| [_mm256_cvtepu16_epi32](_mm256_cvtepu16_epi32.md) | convert | [_mm256_cvtepu16_epi32.c](../../../src/example/avx/_mm256_cvtepu16_epi32.c) |
| [_mm256_cvtepu16_epi64](_mm256_cvtepu16_epi64.md) | convert | [_mm256_cvtepu16_epi64.c](../../../src/example/avx/_mm256_cvtepu16_epi64.c) |
| [_mm256_cvtepu32_epi64](_mm256_cvtepu32_epi64.md) | convert | [_mm256_cvtepu32_epi64.c](../../../src/example/avx/_mm256_cvtepu32_epi64.c) |
| [_mm256_cvtepu8_epi16](_mm256_cvtepu8_epi16.md) | convert | [_mm256_cvtepu8_epi16.c](../../../src/example/avx/_mm256_cvtepu8_epi16.c) |
| [_mm256_cvtepu8_epi32](_mm256_cvtepu8_epi32.md) | convert | [_mm256_cvtepu8_epi32.c](../../../src/example/avx/_mm256_cvtepu8_epi32.c) |
| [_mm256_cvtepu8_epi64](_mm256_cvtepu8_epi64.md) | convert | [_mm256_cvtepu8_epi64.c](../../../src/example/avx/_mm256_cvtepu8_epi64.c) |
| [_mm256_cvtpd_epi32](_mm256_cvtpd_epi32.md) | convert | [_mm256_cvtpd_epi32.c](../../../src/example/avx/_mm256_cvtpd_epi32.c) |
| [_mm256_cvtpd_ps](_mm256_cvtpd_ps.md) | convert | [_mm256_cvtpd_ps.c](../../../src/example/avx/_mm256_cvtpd_ps.c) |
| [_mm256_cvtps_epi32](_mm256_cvtps_epi32.md) | convert | [_mm256_cvtps_epi32.c](../../../src/example/avx/_mm256_cvtps_epi32.c) |
| [_mm256_cvtps_pd](_mm256_cvtps_pd.md) | convert | [_mm256_cvtps_pd.c](../../../src/example/avx/_mm256_cvtps_pd.c) |
| [_mm256_cvtsd_f64](_mm256_cvtsd_f64.md) | convert | [_mm256_cvtsd_f64.c](../../../src/example/avx/_mm256_cvtsd_f64.c) |
| [_mm256_cvtsi256_si32](_mm256_cvtsi256_si32.md) | convert | [_mm256_cvtsi256_si32.c](../../../src/example/avx/_mm256_cvtsi256_si32.c) |
| [_mm256_cvtss_f32](_mm256_cvtss_f32.md) | convert | [_mm256_cvtss_f32.c](../../../src/example/avx/_mm256_cvtss_f32.c) |
| [_mm256_cvttpd_epi32](_mm256_cvttpd_epi32.md) | convert | [_mm256_cvttpd_epi32.c](../../../src/example/avx/_mm256_cvttpd_epi32.c) |
| [_mm256_cvttps_epi32](_mm256_cvttps_epi32.md) | convert | [_mm256_cvttps_epi32.c](../../../src/example/avx/_mm256_cvttps_epi32.c) |
| [_mm256_div_pd](_mm256_div_pd.md) | divide | [_mm256_div_pd.c](../../../src/example/avx/_mm256_div_pd.c) |
| [_mm256_div_ps](_mm256_div_ps.md) | divide | [_mm256_div_ps.c](../../../src/example/avx/_mm256_div_ps.c) |
| [_mm256_dp_ps](_mm256_dp_ps.md) | conditional multiply and sum | [_mm256_dp_ps.c](../../../src/example/avx/_mm256_dp_ps.c) |
| [_mm256_extract_epi16](_mm256_extract_epi16.md) | extract | [_mm256_extract_epi16.c](../../../src/example/avx/_mm256_extract_epi16.c) |
| [_mm256_extract_epi32](_mm256_extract_epi32.md) | extract | [_mm256_extract_epi32.c](../../../src/example/avx/_mm256_extract_epi32.c) |
| [_mm256_extract_epi64](_mm256_extract_epi64.md) | extract | [_mm256_extract_epi64.c](../../../src/example/avx/_mm256_extract_epi64.c) |
| [_mm256_extract_epi8](_mm256_extract_epi8.md) | extract | [_mm256_extract_epi8.c](../../../src/example/avx/_mm256_extract_epi8.c) |
| [_mm256_extractf128_pd](_mm256_extractf128_pd.md) | extract | [_mm256_extractf128_pd.c](../../../src/example/avx/_mm256_extractf128_pd.c) |
| [_mm256_extractf128_ps](_mm256_extractf128_ps.md) | extract | [_mm256_extractf128_ps.c](../../../src/example/avx/_mm256_extractf128_ps.c) |
| [_mm256_extractf128_si256](_mm256_extractf128_si256.md) | extract | [_mm256_extractf128_si256.c](../../../src/example/avx/_mm256_extractf128_si256.c) |
| [_mm256_extracti128_si256](_mm256_extracti128_si256.md) | extract | [_mm256_extracti128_si256.c](../../../src/example/avx/_mm256_extracti128_si256.c) |
| [_mm256_floor_pd](_mm256_floor_pd.md) | floor | [_mm256_floor_pd.c](../../../src/example/avx/_mm256_floor_pd.c) |
| [_mm256_floor_ps](_mm256_floor_ps.md) | floor | [_mm256_floor_ps.c](../../../src/example/avx/_mm256_floor_ps.c) |
| [_mm256_hadd_epi16](_mm256_hadd_epi16.md) | horizontal add | [_mm256_hadd_epi16.c](../../../src/example/avx/_mm256_hadd_epi16.c) |
| [_mm256_hadd_epi32](_mm256_hadd_epi32.md) | horizontal add | [_mm256_hadd_epi32.c](../../../src/example/avx/_mm256_hadd_epi32.c) |
| [_mm256_hadd_pd](_mm256_hadd_pd.md) | horizontal add | [_mm256_hadd_pd.c](../../../src/example/avx/_mm256_hadd_pd.c) |
| [_mm256_hadd_ps](_mm256_hadd_ps.md) | horizontal add | [_mm256_hadd_ps.c](../../../src/example/avx/_mm256_hadd_ps.c) |
| [_mm256_hadds_epi16](_mm256_hadds_epi16.md) | horizontal add saturation | [_mm256_hadds_epi16.c](../../../src/example/avx/_mm256_hadds_epi16.c) |
| [_mm256_hsub_epi16](_mm256_hsub_epi16.md) | horizontal sub | [_mm256_hsub_epi16.c](../../../src/example/avx/_mm256_hsub_epi16.c) |
| [_mm256_hsub_epi32](_mm256_hsub_epi32.md) | horizontal sub | [_mm256_hsub_epi32.c](../../../src/example/avx/_mm256_hsub_epi32.c) |
| [_mm256_hsub_pd](_mm256_hsub_pd.md) | horizontal sub | [_mm256_hsub_pd.c](../../../src/example/avx/_mm256_hsub_pd.c) |
| [_mm256_hsub_ps](_mm256_hsub_ps.md) | horizontal sub | [_mm256_hsub_ps.c](../../../src/example/avx/_mm256_hsub_ps.c) |
| [_mm256_hsubs_epi16](_mm256_hsubs_epi16.md) | horizontal sub saturation | [_mm256_hsubs_epi16.c](../../../src/example/avx/_mm256_hsubs_epi16.c) |
| [_mm256_i32gather_epi32](_mm256_i32gather_epi32.md) | gather | [_mm256_i32gather_epi32.c](../../../src/example/avx/_mm256_i32gather_epi32.c) |
| [_mm256_i32gather_epi64](_mm256_i32gather_epi64.md) | gather | [_mm256_i32gather_epi64.c](../../../src/example/avx/_mm256_i32gather_epi64.c) |
| [_mm256_i32gather_pd](_mm256_i32gather_pd.md) | gather | [_mm256_i32gather_pd.c](../../../src/example/avx/_mm256_i32gather_pd.c) |
| [_mm256_i32gather_ps](_mm256_i32gather_ps.md) | gather | [_mm256_i32gather_ps.c](../../../src/example/avx/_mm256_i32gather_ps.c) |
| [_mm256_i64gather_epi32](_mm256_i64gather_epi32.md) | gather | [_mm256_i64gather_epi32.c](../../../src/example/avx/_mm256_i64gather_epi32.c) |
| [_mm256_i64gather_epi64](_mm256_i64gather_epi64.md) | gather | [_mm256_i64gather_epi64.c](../../../src/example/avx/_mm256_i64gather_epi64.c) |
| [_mm256_i64gather_pd](_mm256_i64gather_pd.md) | gather | [_mm256_i64gather_pd.c](../../../src/example/avx/_mm256_i64gather_pd.c) |
| [_mm256_i64gather_ps](_mm256_i64gather_ps.md) | gather | [_mm256_i64gather_ps.c](../../../src/example/avx/_mm256_i64gather_ps.c) |
| [_mm256_insert_epi16](_mm256_insert_epi16.md) | insert | [_mm256_insert_epi16.c](../../../src/example/avx/_mm256_insert_epi16.c) |
| [_mm256_insert_epi32](_mm256_insert_epi32.md) | insert | [_mm256_insert_epi32.c](../../../src/example/avx/_mm256_insert_epi32.c) |
| [_mm256_insert_epi64](_mm256_insert_epi64.md) | insert | [_mm256_insert_epi64.c](../../../src/example/avx/_mm256_insert_epi64.c) |
| [_mm256_insert_epi8](_mm256_insert_epi8.md) | insert | [_mm256_insert_epi8.c](../../../src/example/avx/_mm256_insert_epi8.c) |
| [_mm256_insertf128_pd](_mm256_insertf128_pd.md) | insert | [_mm256_insertf128_pd.c](../../../src/example/avx/_mm256_insertf128_pd.c) |
| [_mm256_insertf128_ps](_mm256_insertf128_ps.md) | insert | [_mm256_insertf128_ps.c](../../../src/example/avx/_mm256_insertf128_ps.c) |
| [_mm256_insertf128_si256](_mm256_insertf128_si256.md) | insert | [_mm256_insertf128_si256.c](../../../src/example/avx/_mm256_insertf128_si256.c) |
| [_mm256_inserti128_si256](_mm256_inserti128_si256.md) | insert | [_mm256_inserti128_si256.c](../../../src/example/avx/_mm256_inserti128_si256.c) |
| [_mm256_lddqu_si256](_mm256_lddqu_si256.md) | load | [_mm256_lddqu_si256.c](../../../src/example/avx/_mm256_lddqu_si256.c) |
| [_mm256_load_pd](_mm256_load_pd.md) | load | [_mm256_load_pd.c](../../../src/example/avx/_mm256_load_pd.c) |
| [_mm256_load_ps](_mm256_load_ps.md) | load | [_mm256_load_ps.c](../../../src/example/avx/_mm256_load_ps.c) |
| [_mm256_load_si256](_mm256_load_si256.md) | load | [_mm256_load_si256.c](../../../src/example/avx/_mm256_load_si256.c) |
| [_mm256_loadu2_m128d](_mm256_loadu2_m128d.md) | load | [_mm256_loadu2_m128d.c](../../../src/example/avx/_mm256_loadu2_m128d.c) |
| [_mm256_loadu2_m128i](_mm256_loadu2_m128i.md) | load | [_mm256_loadu2_m128i.c](../../../src/example/avx/_mm256_loadu2_m128i.c) |
| [_mm256_loadu2_m128](_mm256_loadu2_m128.md) | load | [_mm256_loadu2_m128.c](../../../src/example/avx/_mm256_loadu2_m128.c) |
| [_mm256_loadu_pd](_mm256_loadu_pd.md) | load | [_mm256_loadu_pd.c](../../../src/example/avx/_mm256_loadu_pd.c) |
| [_mm256_loadu_ps](_mm256_loadu_ps.md) | load | [_mm256_loadu_ps.c](../../../src/example/avx/_mm256_loadu_ps.c) |
| [_mm256_loadu_si256](_mm256_loadu_si256.md) | load | [_mm256_loadu_si256.c](../../../src/example/avx/_mm256_loadu_si256.c) |
| [_mm256_madd_epi16](_mm256_madd_epi16.md) | multiply and add | [_mm256_madd_epi16.c](../../../src/example/avx/_mm256_madd_epi16.c) |
| [_mm256_maddubs_epi16](_mm256_maddubs_epi16.md) | vertically multiply and saturation add | [_mm256_maddubs_epi16.c](../../../src/example/avx/_mm256_maddubs_epi16.c) |
| [_mm256_mask_i32gather_epi32](_mm256_mask_i32gather_epi32.md) | gather | [_mm256_mask_i32gather_epi32.c](../../../src/example/avx/_mm256_mask_i32gather_epi32.c) |
| [_mm256_mask_i32gather_epi64](_mm256_mask_i32gather_epi64.md) | gather | [_mm256_mask_i32gather_epi64.c](../../../src/example/avx/_mm256_mask_i32gather_epi64.c) |
| [_mm256_mask_i32gather_pd](_mm256_mask_i32gather_pd.md) | gather | [_mm256_mask_i32gather_pd.c](../../../src/example/avx/_mm256_mask_i32gather_pd.c) |
| [_mm256_mask_i32gather_ps](_mm256_mask_i32gather_ps.md) | gather | [_mm256_mask_i32gather_ps.c](../../../src/example/avx/_mm256_mask_i32gather_ps.c) |
| [_mm256_mask_i64gather_epi32](_mm256_mask_i64gather_epi32.md) | gather | [_mm256_mask_i64gather_epi32.c](../../../src/example/avx/_mm256_mask_i64gather_epi32.c) |
| [_mm256_mask_i64gather_epi64](_mm256_mask_i64gather_epi64.md) | gather | [_mm256_mask_i64gather_epi64.c](../../../src/example/avx/_mm256_mask_i64gather_epi64.c) |
| [_mm256_mask_i64gather_pd](_mm256_mask_i64gather_pd.md) | gather | [_mm256_mask_i64gather_pd.c](../../../src/example/avx/_mm256_mask_i64gather_pd.c) |
| [_mm256_mask_i64gather_ps](_mm256_mask_i64gather_ps.md) | gather | [_mm256_mask_i64gather_ps.c](../../../src/example/avx/_mm256_mask_i64gather_ps.c) |
| [_mm256_maskload_epi32](_mm256_maskload_epi32.md) | load (mask) | [_mm256_maskload_epi32.c](../../../src/example/avx/_mm256_maskload_epi32.c) |
| [_mm256_maskload_epi64](_mm256_maskload_epi64.md) | load (mask) | [_mm256_maskload_epi64.c](../../../src/example/avx/_mm256_maskload_epi64.c) |
| [_mm256_maskload_pd](_mm256_maskload_pd.md) | load (mask) | [_mm256_maskload_pd.c](../../../src/example/avx/_mm256_maskload_pd.c) |
| [_mm256_maskload_ps](_mm256_maskload_ps.md) | load (mask) | [_mm256_maskload_ps.c](../../../src/example/avx/_mm256_maskload_ps.c) |
| [_mm256_maskstore_epi32](_mm256_maskstore_epi32.md) | store (mask) | [_mm256_maskstore_epi32.c](../../../src/example/avx/_mm256_maskstore_epi32.c) |
| [_mm256_maskstore_epi64](_mm256_maskstore_epi64.md) | store(mask) | [_mm256_maskstore_epi64.c](../../../src/example/avx/_mm256_maskstore_epi64.c) |
| [_mm256_maskstore_pd](_mm256_maskstore_pd.md) | store(mask) | [_mm256_maskstore_pd.c](../../../src/example/avx/_mm256_maskstore_pd.c) |
| [_mm256_maskstore_ps](_mm256_maskstore_ps.md) | store(mask) | [_mm256_maskstore_ps.c](../../../src/example/avx/_mm256_maskstore_ps.c) |
| [_mm256_max_epi16](_mm256_max_epi16.md) | max | [_mm256_max_epi16.c](../../../src/example/avx/_mm256_max_epi16.c) |
| [_mm256_max_epi32](_mm256_max_epi32.md) | max | [_mm256_max_epi32.c](../../../src/example/avx/_mm256_max_epi32.c) |
| [_mm256_max_epi8](_mm256_max_epi8.md) | max | [_mm256_max_epi8.c](../../../src/example/avx/_mm256_max_epi8.c) |
| [_mm256_max_epu16](_mm256_max_epu16.md) | max | [_mm256_max_epu16.c](../../../src/example/avx/_mm256_max_epu16.c) |
| [_mm256_max_epu32](_mm256_max_epu32.md) | max | [_mm256_max_epu32.c](../../../src/example/avx/_mm256_max_epu32.c) |
| [_mm256_max_epu8](_mm256_max_epu8.md) | max | [_mm256_max_epu8.c](../../../src/example/avx/_mm256_max_epu8.c) |
| [_mm256_max_pd](_mm256_max_pd.md) | max | [_mm256_max_pd.c](../../../src/example/avx/_mm256_max_pd.c) |
| [_mm256_max_ps](_mm256_max_ps.md) | max | [_mm256_max_ps.c](../../../src/example/avx/_mm256_max_ps.c) |
| [_mm256_min_epi16](_mm256_min_epi16.md) | min | [_mm256_min_epi16.c](../../../src/example/avx/_mm256_min_epi16.c) |
| [_mm256_min_epi32](_mm256_min_epi32.md) | min | [_mm256_min_epi32.c](../../../src/example/avx/_mm256_min_epi32.c) |
| [_mm256_min_epi8](_mm256_min_epi8.md) | min | [_mm256_min_epi8.c](../../../src/example/avx/_mm256_min_epi8.c) |
| [_mm256_min_epu16](_mm256_min_epu16.md) | min | [_mm256_min_epu16.c](../../../src/example/avx/_mm256_min_epu16.c) |
| [_mm256_min_epu32](_mm256_min_epu32.md) | min | [_mm256_min_epu32.c](../../../src/example/avx/_mm256_min_epu32.c) |
| [_mm256_min_epu8](_mm256_min_epu8.md) | min | [_mm256_min_epu8.c](../../../src/example/avx/_mm256_min_epu8.c) |
| [_mm256_min_pd](_mm256_min_pd.md) | min | [_mm256_min_pd.c](../../../src/example/avx/_mm256_min_pd.c) |
| [_mm256_min_ps](_mm256_min_ps.md) | min | [_mm256_min_ps.c](../../../src/example/avx/_mm256_min_ps.c) |
| [_mm256_movedup_pd](_mm256_movedup_pd.md) | move dup | [_mm256_movedup_pd.c](../../../src/example/avx/_mm256_movedup_pd.c) |
| [_mm256_movehdup_ps](_mm256_movehdup_ps.md) | move dup | [_mm256_movehdup_ps.c](../../../src/example/avx/_mm256_movehdup_ps.c) |
| [_mm256_moveldup_ps](_mm256_moveldup_ps.md) | move dup | [_mm256_moveldup_ps.c](../../../src/example/avx/_mm256_moveldup_ps.c) |
| [_mm256_movemask_epi8](_mm256_movemask_epi8.md) | move mask | [_mm256_movemask_epi8.c](../../../src/example/avx/_mm256_movemask_epi8.c) |
| [_mm256_movemask_pd](_mm256_movemask_pd.md) | move mask | [_mm256_movemask_pd.c](../../../src/example/avx/_mm256_movemask_pd.c) |
| [_mm256_movemask_ps](_mm256_movemask_ps.md) | move mask | [_mm256_movemask_ps.c](../../../src/example/avx/_mm256_movemask_ps.c) |
| [_mm256_mpsadbw_epu8](_mm256_mpsadbw_epu8.md) | compute the sum of absolute differences (SAD) | [_mm256_mpsadbw_epu8.c](../../../src/example/avx/_mm256_mpsadbw_epu8.c) |
| [_mm256_mul_epi32](_mm256_mul_epi32.md) | multiply | [_mm256_mul_epi32.c](../../../src/example/avx/_mm256_mul_epi32.c) |
| [_mm256_mul_epu32](_mm256_mul_epu32.md) | multiply | [_mm256_mul_epu32.c](../../../src/example/avx/_mm256_mul_epu32.c) |
| [_mm256_mulhi_epi16](_mm256_mulhi_epi16.md) | multiply | [_mm256_mulhi_epi16.c](../../../src/example/avx/_mm256_mulhi_epi16.c) |
| [_mm256_mulhi_epu16](_mm256_mulhi_epu16.md) | multiply | [_mm256_mulhi_epu16.c](../../../src/example/avx/_mm256_mulhi_epu16.c) |
| [_mm256_mulhrs_epi16](_mm256_mulhrs_epi16.md) | multiply | [_mm256_mulhrs_epi16.c](../../../src/example/avx/_mm256_mulhrs_epi16.c) |
| [_mm256_mullo_epi16](_mm256_mullo_epi16.md) | multiply | [_mm256_mullo_epi16.c](../../../src/example/avx/_mm256_mullo_epi16.c) |
| [_mm256_mullo_epi32](_mm256_mullo_epi32.md) | multiply | [_mm256_mullo_epi32.c](../../../src/example/avx/_mm256_mullo_epi32.c) |
| [_mm256_mul_pd](_mm256_mul_pd.md) | multiply | [_mm256_mul_pd.c](../../../src/example/avx/_mm256_mul_pd.c) |
| [_mm256_mul_ps](_mm256_mul_ps.md) | multiply | [_mm256_mul_ps.c](../../../src/example/avx/_mm256_mul_ps.c) |
| [_mm256_or_pd](_mm256_or_pd.md) | or | [_mm256_or_pd.c](../../../src/example/avx/_mm256_or_pd.c) |
| [_mm256_or_ps](_mm256_or_ps.md) | or | [_mm256_or_ps.c](../../../src/example/avx/_mm256_or_ps.c) |
| [_mm256_or_si256](_mm256_or_si256.md) | - | [_mm256_or_si256.c](../../../src/example/avx/_mm256_or_si256.c) |
| [_mm256_packs_epi16](_mm256_packs_epi16.md) | pack saturation | [_mm256_packs_epi16.c](../../../src/example/avx/_mm256_packs_epi16.c) |
| [_mm256_packs_epi32](_mm256_packs_epi32.md) | pack saturation | [_mm256_packs_epi32.c](../../../src/example/avx/_mm256_packs_epi32.c) |
| [_mm256_packus_epi16](_mm256_packus_epi16.md) | pack saturation | [_mm256_packus_epi16.c](../../../src/example/avx/_mm256_packus_epi16.c) |
| [_mm256_packus_epi32](_mm256_packus_epi32.md) | pack saturation | [_mm256_packus_epi32.c](../../../src/example/avx/_mm256_packus_epi32.c) |
| [_mm256_permute2f128_pd](_mm256_permute2f128_pd.md) | shuffle | [_mm256_permute2f128_pd.c](../../../src/example/avx/_mm256_permute2f128_pd.c) |
| [_mm256_permute2f128_ps](_mm256_permute2f128_ps.md) | shuffle | [_mm256_permute2f128_ps.c](../../../src/example/avx/_mm256_permute2f128_ps.c) |
| [_mm256_permute2f128_si256](_mm256_permute2f128_si256.md) | shuffle | [_mm256_permute2f128_si256.c](../../../src/example/avx/_mm256_permute2f128_si256.c) |
| [_mm256_permute2x128_si256](_mm256_permute2x128_si256.md) | shuffle | [_mm256_permute2x128_si256.c](../../../src/example/avx/_mm256_permute2x128_si256.c) |
| [_mm256_permute4x64_epi64](_mm256_permute4x64_epi64.md) | shuffle | [_mm256_permute4x64_epi64.c](../../../src/example/avx/_mm256_permute4x64_epi64.c) |
| [_mm256_permute4x64_pd](_mm256_permute4x64_pd.md) | shuffle | [_mm256_permute4x64_pd.c](../../../src/example/avx/_mm256_permute4x64_pd.c) |
| [_mm256_permute_ps](_mm256_permute_ps.md) | shuffle | [_mm256_permute_ps.c](../../../src/example/avx/_mm256_permute_ps.c) |
| [_mm256_permutevar8x32_epi32](_mm256_permutevar8x32_epi32.md) | shuffle | [_mm256_permutevar8x32_epi32.c](../../../src/example/avx/_mm256_permutevar8x32_epi32.c) |
| [_mm256_permutevar8x32_ps](_mm256_permutevar8x32_ps.md) | shuffle | [_mm256_permutevar8x32_ps.c](../../../src/example/avx/_mm256_permutevar8x32_ps.c) |
| [_mm256_permutevar_ps](_mm256_permutevar_ps.md) | shuffle | [_mm256_permutevar_ps.c](../../../src/example/avx/_mm256_permutevar_ps.c) |
| [_mm256_rcp_ps](_mm256_rcp_ps.md) | reciprocal | [_mm256_rcp_ps.c](../../../src/example/avx/_mm256_rcp_ps.c) |
| [_mm256_round_pd](_mm256_round_pd.md) | round | [_mm256_round_pd.c](../../../src/example/avx/_mm256_round_pd.c) |
| [_mm256_round_ps](_mm256_round_ps.md) | round | [_mm256_round_ps.c](../../../src/example/avx/_mm256_round_ps.c) |
| [_mm256_rsqrt_ps](_mm256_rsqrt_ps.md) | reciprocal square root | [_mm256_rsqrt_ps.c](../../../src/example/avx/_mm256_rsqrt_ps.c) |
| [_mm256_sad_epu8](_mm256_sad_epu8.md) | the absolute differences | [_mm256_sad_epu8.c](../../../src/example/avx/_mm256_sad_epu8.c) |
| [_mm256_set1_epi16](_mm256_set1_epi16.md) | set | [_mm256_set1_epi16.c](../../../src/example/avx/_mm256_set1_epi16.c) |
| [_mm256_set1_epi32](_mm256_set1_epi32.md) | set | [_mm256_set1_epi32.c](../../../src/example/avx/_mm256_set1_epi32.c) |
| [_mm256_set1_epi64x](_mm256_set1_epi64x.md) | set | [_mm256_set1_epi64x.c](../../../src/example/avx/_mm256_set1_epi64x.c) |
| [_mm256_set1_epi8](_mm256_set1_epi8.md) | set | [_mm256_set1_epi8.c](../../../src/example/avx/_mm256_set1_epi8.c) |
| [_mm256_set1_pd](_mm256_set1_pd.md) | set | [_mm256_set1_pd.c](../../../src/example/avx/_mm256_set1_pd.c) |
| [_mm256_set1_ps](_mm256_set1_ps.md) | set | [_mm256_set1_ps.c](../../../src/example/avx/_mm256_set1_ps.c) |
| [_mm256_set_epi16](_mm256_set_epi16.md) | set | [_mm256_set_epi16.c](../../../src/example/avx/_mm256_set_epi16.c) |
| [_mm256_set_epi32](_mm256_set_epi32.md) | set | [_mm256_set_epi32.c](../../../src/example/avx/_mm256_set_epi32.c) |
| [_mm256_set_epi64x](_mm256_set_epi64x.md) | set | [_mm256_set_epi64x.c](../../../src/example/avx/_mm256_set_epi64x.c) |
| [_mm256_set_epi8](_mm256_set_epi8.md) | set | [_mm256_set_epi8.c](../../../src/example/avx/_mm256_set_epi8.c) |
| [_mm256_set_m128d](_mm256_set_m128d.md) | set | [_mm256_set_m128d.c](../../../src/example/avx/_mm256_set_m128d.c) |
| [_mm256_set_m128i](_mm256_set_m128i.md) | set | [_mm256_set_m128i.c](../../../src/example/avx/_mm256_set_m128i.c) |
| [_mm256_set_m128](_mm256_set_m128.md) | set | [_mm256_set_m128.c](../../../src/example/avx/_mm256_set_m128.c) |
| [_mm256_set_pd](_mm256_set_pd.md) | set | [_mm256_set_pd.c](../../../src/example/avx/_mm256_set_pd.c) |
| [_mm256_set_ps](_mm256_set_ps.md) | set | [_mm256_set_ps.c](../../../src/example/avx/_mm256_set_ps.c) |
| [_mm256_setr_epi16](_mm256_setr_epi16.md) | ser | [_mm256_setr_epi16.c](../../../src/example/avx/_mm256_setr_epi16.c) |
| [_mm256_setr_epi32](_mm256_setr_epi32.md) | set | [_mm256_setr_epi32.c](../../../src/example/avx/_mm256_setr_epi32.c) |
| [_mm256_setr_epi64x](_mm256_setr_epi64x.md) | set | [_mm256_setr_epi64x.c](../../../src/example/avx/_mm256_setr_epi64x.c) |
| [_mm256_setr_epi8](_mm256_setr_epi8.md) | set | [_mm256_setr_epi8.c](../../../src/example/avx/_mm256_setr_epi8.c) |
| [_mm256_setr_m128d](_mm256_setr_m128d.md) | set | [_mm256_setr_m128d.c](../../../src/example/avx/_mm256_setr_m128d.c) |
| [_mm256_setr_m128i](_mm256_setr_m128i.md) | set | [_mm256_setr_m128i.c](../../../src/example/avx/_mm256_setr_m128i.c) |
| [_mm256_setr_m128](_mm256_setr_m128.md) | set | [_mm256_setr_m128.c](../../../src/example/avx/_mm256_setr_m128.c) |
| [_mm256_setr_pd](_mm256_setr_pd.md) | set | [_mm256_setr_pd.c](../../../src/example/avx/_mm256_setr_pd.c) |
| [_mm256_setr_ps](_mm256_setr_ps.md) | set | [_mm256_setr_ps.c](../../../src/example/avx/_mm256_setr_ps.c) |
| [_mm256_setzero_pd](_mm256_setzero_pd.md) | set | [_mm256_setzero_pd.c](../../../src/example/avx/_mm256_setzero_pd.c) |
| [_mm256_setzero_ps](_mm256_setzero_ps.md) | set | [_mm256_setzero_ps.c](../../../src/example/avx/_mm256_setzero_ps.c) |
| [_mm256_setzero_si256](_mm256_setzero_si256.md) | set | [_mm256_setzero_si256.c](../../../src/example/avx/_mm256_setzero_si256.c) |
| [_mm256_shuffle_epi32](_mm256_shuffle_epi32.md) | shuffle | [_mm256_shuffle_epi32.c](../../../src/example/avx/_mm256_shuffle_epi32.c) |
| [_mm256_shuffle_epi8](_mm256_shuffle_epi8.md) | shuffle | [_mm256_shuffle_epi8.c](../../../src/example/avx/_mm256_shuffle_epi8.c) |
| [_mm256_shufflehi_epi16](_mm256_shufflehi_epi16.md) | shuffle | [_mm256_shufflehi_epi16.c](../../../src/example/avx/_mm256_shufflehi_epi16.c) |
| [_mm256_shufflelo_epi16](_mm256_shufflelo_epi16.md) | shuffle | [_mm256_shufflelo_epi16.c](../../../src/example/avx/_mm256_shufflelo_epi16.c) |
| [_mm256_shuffle_pd](_mm256_shuffle_pd.md) | shuffle | [_mm256_shuffle_pd.c](../../../src/example/avx/_mm256_shuffle_pd.c) |
| [_mm256_shuffle_ps](_mm256_shuffle_ps.md) | shuffle | [_mm256_shuffle_ps.c](../../../src/example/avx/_mm256_shuffle_ps.c) |
| [_mm256_sign_epi16](_mm256_sign_epi16.md) | sign | [_mm256_sign_epi16.c](../../../src/example/avx/_mm256_sign_epi16.c) |
| [_mm256_sign_epi32](_mm256_sign_epi32.md) | sign | [_mm256_sign_epi32.c](../../../src/example/avx/_mm256_sign_epi32.c) |
| [_mm256_sign_epi8](_mm256_sign_epi8.md) | sign | [_mm256_sign_epi8.c](../../../src/example/avx/_mm256_sign_epi8.c) |
| [_mm256_sll_epi16](_mm256_sll_epi16.md) | shift left | [_mm256_sll_epi16.c](../../../src/example/avx/_mm256_sll_epi16.c) |
| [_mm256_sll_epi32](_mm256_sll_epi32.md) | shift left | [_mm256_sll_epi32.c](../../../src/example/avx/_mm256_sll_epi32.c) |
| [_mm256_sll_epi64](_mm256_sll_epi64.md) | shift left | [_mm256_sll_epi64.c](../../../src/example/avx/_mm256_sll_epi64.c) |
| [_mm256_slli_epi16](_mm256_slli_epi16.md) | shift left | [_mm256_slli_epi16.c](../../../src/example/avx/_mm256_slli_epi16.c) |
| [_mm256_slli_epi32](_mm256_slli_epi32.md) | shift left | [_mm256_slli_epi32.c](../../../src/example/avx/_mm256_slli_epi32.c) |
| [_mm256_slli_epi64](_mm256_slli_epi64.md) | shift left | [_mm256_slli_epi64.c](../../../src/example/avx/_mm256_slli_epi64.c) |
| [_mm256_slli_si256](_mm256_slli_si256.md) | shift left | [_mm256_slli_si256.c](../../../src/example/avx/_mm256_slli_si256.c) |
| [_mm256_sllv_epi32](_mm256_sllv_epi32.md) | shift left | [_mm256_sllv_epi32.c](../../../src/example/avx/_mm256_sllv_epi32.c) |
| [_mm256_sllv_epi64](_mm256_sllv_epi64.md) | shift left | [_mm256_sllv_epi64.c](../../../src/example/avx/_mm256_sllv_epi64.c) |
| [_mm256_sqrt_pd](_mm256_sqrt_pd.md) | square root | [_mm256_sqrt_pd.c](../../../src/example/avx/_mm256_sqrt_pd.c) |
| [_mm256_sqrt_ps](_mm256_sqrt_ps.md) | square root | [_mm256_sqrt_ps.c](../../../src/example/avx/_mm256_sqrt_ps.c) |
| [_mm256_sra_epi16](_mm256_sra_epi16.md) | shift right | [_mm256_sra_epi16.c](../../../src/example/avx/_mm256_sra_epi16.c) |
| [_mm256_sra_epi32](_mm256_sra_epi32.md) | shift right | [_mm256_sra_epi32.c](../../../src/example/avx/_mm256_sra_epi32.c) |
| [_mm256_srai_epi16](_mm256_srai_epi16.md) | shift right | [_mm256_srai_epi16.c](../../../src/example/avx/_mm256_srai_epi16.c) |
| [_mm256_srai_epi32](_mm256_srai_epi32.md) | shift right | [_mm256_srai_epi32.c](../../../src/example/avx/_mm256_srai_epi32.c) |
| [_mm256_srav_epi32](_mm256_srav_epi32.md) | shift right | [_mm256_srav_epi32.c](../../../src/example/avx/_mm256_srav_epi32.c) |
| [_mm256_srl_epi16](_mm256_srl_epi16.md) | shift right | [_mm256_srl_epi16.c](../../../src/example/avx/_mm256_srl_epi16.c) |
| [_mm256_srl_epi32](_mm256_srl_epi32.md) | shift right | [_mm256_srl_epi32.c](../../../src/example/avx/_mm256_srl_epi32.c) |
| [_mm256_srl_epi64](_mm256_srl_epi64.md) | shift right | [_mm256_srl_epi64.c](../../../src/example/avx/_mm256_srl_epi64.c) |
| [_mm256_srli_epi16](_mm256_srli_epi16.md) | shift right | [_mm256_srli_epi16.c](../../../src/example/avx/_mm256_srli_epi16.c) |
| [_mm256_srli_epi32](_mm256_srli_epi32.md) | shift right | [_mm256_srli_epi32.c](../../../src/example/avx/_mm256_srli_epi32.c) |
| [_mm256_srli_epi64](_mm256_srli_epi64.md) | shift right | [_mm256_srli_epi64.c](../../../src/example/avx/_mm256_srli_epi64.c) |
| [_mm256_srli_si256](_mm256_srli_si256.md) | shift right | [_mm256_srli_si256.c](../../../src/example/avx/_mm256_srli_si256.c) |
| [_mm256_srlv_epi32](_mm256_srlv_epi32.md) | shift right | [_mm256_srlv_epi32.c](../../../src/example/avx/_mm256_srlv_epi32.c) |
| [_mm256_srlv_epi64](_mm256_srlv_epi64.md) | shift right | [_mm256_srlv_epi64.c](../../../src/example/avx/_mm256_srlv_epi64.c) |
| [_mm256_store_pd](_mm256_store_pd.md) | store | [_mm256_store_pd.c](../../../src/example/avx/_mm256_store_pd.c) |
| [_mm256_store_ps](_mm256_store_ps.md) | store | [_mm256_store_ps.c](../../../src/example/avx/_mm256_store_ps.c) |
| [_mm256_store_si256](_mm256_store_si256.md) | store | [_mm256_store_si256.c](../../../src/example/avx/_mm256_store_si256.c) |
| [_mm256_storeu2_m128d](_mm256_storeu2_m128d.md) | store | [_mm256_storeu2_m128d.c](../../../src/example/avx/_mm256_storeu2_m128d.c) |
| [_mm256_storeu2_m128i](_mm256_storeu2_m128i.md) | store | [_mm256_storeu2_m128i.c](../../../src/example/avx/_mm256_storeu2_m128i.c) |
| [_mm256_storeu2_m128](_mm256_storeu2_m128.md) | store | [_mm256_storeu2_m128.c](../../../src/example/avx/_mm256_storeu2_m128.c) |
| [_mm256_storeu_pd](_mm256_storeu_pd.md) | store | [_mm256_storeu_pd.c](../../../src/example/avx/_mm256_storeu_pd.c) |
| [_mm256_storeu_ps](_mm256_storeu_ps.md) | store | [_mm256_storeu_ps.c](../../../src/example/avx/_mm256_storeu_ps.c) |
| [_mm256_storeu_si256](_mm256_storeu_si256.md) | store | [_mm256_storeu_si256.c](../../../src/example/avx/_mm256_storeu_si256.c) |
| [_mm256_stream_load_si256](_mm256_stream_load_si256.md) | load | [_mm256_stream_load_si256.c](../../../src/example/avx/_mm256_stream_load_si256.c) |
| [_mm256_stream_pd](_mm256_stream_pd.md) | load | [_mm256_stream_pd.c](../../../src/example/avx/_mm256_stream_pd.c) |
| [_mm256_stream_ps](_mm256_stream_ps.md) | load | [_mm256_stream_ps.c](../../../src/example/avx/_mm256_stream_ps.c) |
| [_mm256_stream_si256](_mm256_stream_si256.md) | load | [_mm256_stream_si256.c](../../../src/example/avx/_mm256_stream_si256.c) |
| [_mm256_sub_epi16](_mm256_sub_epi16.md) | sub | [_mm256_sub_epi16.c](../../../src/example/avx/_mm256_sub_epi16.c) |
| [_mm256_sub_epi32](_mm256_sub_epi32.md) | sub | [_mm256_sub_epi32.c](../../../src/example/avx/_mm256_sub_epi32.c) |
| [_mm256_sub_epi64](_mm256_sub_epi64.md) | sub | [_mm256_sub_epi64.c](../../../src/example/avx/_mm256_sub_epi64.c) |
| [_mm256_sub_epi8](_mm256_sub_epi8.md) | sub | [_mm256_sub_epi8.c](../../../src/example/avx/_mm256_sub_epi8.c) |
| [_mm256_sub_pd](_mm256_sub_pd.md) | sub | [_mm256_sub_pd.c](../../../src/example/avx/_mm256_sub_pd.c) |
| [_mm256_sub_ps](_mm256_sub_ps.md) | sub | [_mm256_sub_ps.c](../../../src/example/avx/_mm256_sub_ps.c) |
| [_mm256_subs_epi16](_mm256_subs_epi16.md) | sub saturation | [_mm256_subs_epi16.c](../../../src/example/avx/_mm256_subs_epi16.c) |
| [_mm256_subs_epi8](_mm256_subs_epi8.md) | sub saturation | [_mm256_subs_epi8.c](../../../src/example/avx/_mm256_subs_epi8.c) |
| [_mm256_subs_epu16](_mm256_subs_epu16.md) | sub saturation | [_mm256_subs_epu16.c](../../../src/example/avx/_mm256_subs_epu16.c) |
| [_mm256_subs_epu8](_mm256_subs_epu8.md) | sub saturation | [_mm256_subs_epu8.c](../../../src/example/avx/_mm256_subs_epu8.c) |
| [_mm256_testc_pd](_mm256_testc_pd.md) | test cf | [_mm256_testc_pd.c](../../../src/example/avx/_mm256_testc_pd.c) |
| [_mm256_testc_ps](_mm256_testc_ps.md) | test cf | [_mm256_testc_ps.c](../../../src/example/avx/_mm256_testc_ps.c) |
| [_mm256_testc_si256](_mm256_testc_si256.md) | test cf | [_mm256_testc_si256.c](../../../src/example/avx/_mm256_testc_si256.c) |
| [_mm256_testnzc_pd](_mm256_testnzc_pd.md) | test cf & zf | [_mm256_testnzc_pd.c](../../../src/example/avx/_mm256_testnzc_pd.c) |
| [_mm256_testnzc_ps](_mm256_testnzc_ps.md) | test cf & zf | [_mm256_testnzc_ps.c](../../../src/example/avx/_mm256_testnzc_ps.c) |
| [_mm256_testnzc_si256](_mm256_testnzc_si256.md) | test cf & zf | [_mm256_testnzc_si256.c](../../../src/example/avx/_mm256_testnzc_si256.c) |
| [_mm256_testz_pd](_mm256_testz_pd.md) | test zf | [_mm256_testz_pd.c](../../../src/example/avx/_mm256_testz_pd.c) |
| [_mm256_testz_ps](_mm256_testz_ps.md) | test zf | [_mm256_testz_ps.c](../../../src/example/avx/_mm256_testz_ps.c) |
| [_mm256_testz_si256](_mm256_testz_si256.md) | test zf | [_mm256_testz_si256.c](../../../src/example/avx/_mm256_testz_si256.c) |
| [_mm256_undefined_pd](_mm256_undefined_pd.md) | undefined | [_mm256_undefined_pd.c](../../../src/example/avx/_mm256_undefined_pd.c) |
| [_mm256_undefined_ps](_mm256_undefined_ps.md) | undefined | [_mm256_undefined_ps.c](../../../src/example/avx/_mm256_undefined_ps.c) |
| [_mm256_undefined_si256](_mm256_undefined_si256.md) | undefined | [_mm256_undefined_si256.c](../../../src/example/avx/_mm256_undefined_si256.c) |
| [_mm256_unpackhi_epi16](_mm256_unpackhi_epi16.md) | unpack | [_mm256_unpackhi_epi16.c](../../../src/example/avx/_mm256_unpackhi_epi16.c) |
| [_mm256_unpackhi_epi32](_mm256_unpackhi_epi32.md) | unpack | [_mm256_unpackhi_epi32.c](../../../src/example/avx/_mm256_unpackhi_epi32.c) |
| [_mm256_unpackhi_epi64](_mm256_unpackhi_epi64.md) | unpack | [_mm256_unpackhi_epi64.c](../../../src/example/avx/_mm256_unpackhi_epi64.c) |
| [_mm256_unpackhi_epi8](_mm256_unpackhi_epi8.md) | unpack | [_mm256_unpackhi_epi8.c](../../../src/example/avx/_mm256_unpackhi_epi8.c) |
| [_mm256_unpackhi_pd](_mm256_unpackhi_pd.md) | unpack | [_mm256_unpackhi_pd.c](../../../src/example/avx/_mm256_unpackhi_pd.c) |
| [_mm256_unpackhi_ps](_mm256_unpackhi_ps.md) | unpack | [_mm256_unpackhi_ps.c](../../../src/example/avx/_mm256_unpackhi_ps.c) |
| [_mm256_unpacklo_epi16](_mm256_unpacklo_epi16.md) | unpack | [_mm256_unpacklo_epi16.c](../../../src/example/avx/_mm256_unpacklo_epi16.c) |
| [_mm256_unpacklo_epi32](_mm256_unpacklo_epi32.md) | unpack | [_mm256_unpacklo_epi32.c](../../../src/example/avx/_mm256_unpacklo_epi32.c) |
| [_mm256_unpacklo_epi64](_mm256_unpacklo_epi64.md) | unpack | [_mm256_unpacklo_epi64.c](../../../src/example/avx/_mm256_unpacklo_epi64.c) |
| [_mm256_unpacklo_epi8](_mm256_unpacklo_epi8.md) | unpack | [_mm256_unpacklo_epi8.c](../../../src/example/avx/_mm256_unpacklo_epi8.c) |
| [_mm256_unpacklo_pd](_mm256_unpacklo_pd.md) | unpack | [_mm256_unpacklo_pd.c](../../../src/example/avx/_mm256_unpacklo_pd.c) |
| [_mm256_unpacklo_ps](_mm256_unpacklo_ps.md) | unpack | [_mm256_unpacklo_ps.c](../../../src/example/avx/_mm256_unpacklo_ps.c) |
| [_mm256_xor_pd](_mm256_xor_pd.md) | xor | [_mm256_xor_pd.c](../../../src/example/avx/_mm256_xor_pd.c) |
| [_mm256_xor_ps](_mm256_xor_ps.md) | xor | [_mm256_xor_ps.c](../../../src/example/avx/_mm256_xor_ps.c) |
| [_mm256_xor_si256](_mm256_xor_si256.md) | xor | [_mm256_xor_si256.c](../../../src/example/avx/_mm256_xor_si256.c) |
| [_mm256_zeroall](_mm256_zeroall.md) | zero | [_mm256_zeroall.c](../../../src/example/avx/_mm256_zeroall.c) |
| [_mm256_zeroupper](_mm256_zeroupper.md) | zero | [_mm256_zeroupper.c](../../../src/example/avx/_mm256_zeroupper.c) |
| [_mm256_zextpd128_pd256](_mm256_zextpd128_pd256.md) | cast | [_mm256_zextpd128_pd256.c](../../../src/example/avx/_mm256_zextpd128_pd256.c) |
| [_mm256_zextps128_ps256](_mm256_zextps128_ps256.md) | cast | [_mm256_zextps128_ps256.c](../../../src/example/avx/_mm256_zextps128_ps256.c) |
| [_mm256_zextsi128_si256](_mm256_zextsi128_si256.md) | cast | [_mm256_zextsi128_si256.c](../../../src/example/avx/_mm256_zextsi128_si256.c) |
| [_mm_cmp_pd](_mm_cmp_pd.md) | compare | [_mm_cmp_pd.c](../../../src/example/avx/_mm_cmp_pd.c) |
| [_mm_cmp_ps](_mm_cmp_ps.md) | compare | [_mm_cmp_ps.c](../../../src/example/avx/_mm_cmp_ps.c) |
| [_mm_cmp_sd](_mm_cmp_sd.md) | compare | [_mm_cmp_sd.c](../../../src/example/avx/_mm_cmp_sd.c) |
| [_mm_cmp_ss](_mm_cmp_ss.md) | compare | [_mm_cmp_ss.c](../../../src/example/avx/_mm_cmp_ss.c) |
| [_mm_i32gather_epi32](_mm_i32gather_epi32.md) | gather | [_mm_i32gather_epi32.c](../../../src/example/avx/_mm_i32gather_epi32.c) |
| [_mm_i32gather_epi64](_mm_i32gather_epi64.md) | gather | [_mm_i32gather_epi64.c](../../../src/example/avx/_mm_i32gather_epi64.c) |
| [_mm_i32gather_pd](_mm_i32gather_pd.md) | gather | [_mm_i32gather_pd.c](../../../src/example/avx/_mm_i32gather_pd.c) |
| [_mm_i32gather_ps](_mm_i32gather_ps.md) | gather | [_mm_i32gather_ps.c](../../../src/example/avx/_mm_i32gather_ps.c) |
| [_mm_i64gather_epi32](_mm_i64gather_epi32.md) | gather | [_mm_i64gather_epi32.c](../../../src/example/avx/_mm_i64gather_epi32.c) |
| [_mm_i64gather_epi64](_mm_i64gather_epi64.md) | gather | [_mm_i64gather_epi64.c](../../../src/example/avx/_mm_i64gather_epi64.c) |
| [_mm_i64gather_pd](_mm_i64gather_pd.md) | gather | [_mm_i64gather_pd.c](../../../src/example/avx/_mm_i64gather_pd.c) |
| [_mm_i64gather_ps](_mm_i64gather_ps.md) | gather | [_mm_i64gather_ps.c](../../../src/example/avx/_mm_i64gather_ps.c) |
| [_mm_mask_i32gather_epi32](_mm_mask_i32gather_epi32.md) | gather | [_mm_mask_i32gather_epi32.c](../../../src/example/avx/_mm_mask_i32gather_epi32.c) |
| [_mm_mask_i32gather_epi64](_mm_mask_i32gather_epi64.md) | gather | [_mm_mask_i32gather_epi64.c](../../../src/example/avx/_mm_mask_i32gather_epi64.c) |
| [_mm_mask_i32gather_pd](_mm_mask_i32gather_pd.md) | gather | [_mm_mask_i32gather_pd.c](../../../src/example/avx/_mm_mask_i32gather_pd.c) |
| [_mm_mask_i32gather_ps](_mm_mask_i32gather_ps.md) | gather | [_mm_mask_i32gather_ps.c](../../../src/example/avx/_mm_mask_i32gather_ps.c) |
| [_mm_mask_i64gather_epi64](_mm_mask_i64gather_epi64.md) | gather | [_mm_mask_i64gather_epi64.c](../../../src/example/avx/_mm_mask_i64gather_epi64.c) |
| [_mm_mask_i64gather_pd](_mm_mask_i64gather_pd.md) | gather | [_mm_mask_i64gather_pd.c](../../../src/example/avx/_mm_mask_i64gather_pd.c) |
| [_mm_mask_i64gather_ps](_mm_mask_i64gather_ps.md) | gather | [_mm_mask_i64gather_ps.c](../../../src/example/avx/_mm_mask_i64gather_ps.c) |
| [_mm_maskload_epi32](_mm_maskload_epi32.md) | load | [_mm_maskload_epi32.c](../../../src/example/avx/_mm_maskload_epi32.c) |
| [_mm_maskload_epi64](_mm_maskload_epi64.md) | load | [_mm_maskload_epi64.c](../../../src/example/avx/_mm_maskload_epi64.c) |
| [_mm_maskload_pd](_mm_maskload_pd.md) | load | [_mm_maskload_pd.c](../../../src/example/avx/_mm_maskload_pd.c) |
| [_mm_maskload_ps](_mm_maskload_ps.md) | load | [_mm_maskload_ps.c](../../../src/example/avx/_mm_maskload_ps.c) |
| [_mm_maskstore_epi32](_mm_maskstore_epi32.md) | store | [_mm_maskstore_epi32.c](../../../src/example/avx/_mm_maskstore_epi32.c) |
| [_mm_maskstore_epi64](_mm_maskstore_epi64.md) | store | [_mm_maskstore_epi64.c](../../../src/example/avx/_mm_maskstore_epi64.c) |
| [_mm_maskstore_pd](_mm_maskstore_pd.md) | store | [_mm_maskstore_pd.c](../../../src/example/avx/_mm_maskstore_pd.c) |
| [_mm_maskstore_ps](_mm_maskstore_ps.md) | store | [_mm_maskstore_ps.c](../../../src/example/avx/_mm_maskstore_ps.c) |
| [_mm_permute_pd](_mm_permute_pd.md) | shuffle | [_mm_permute_pd.c](../../../src/example/avx/_mm_permute_pd.c) |
| [_mm_permute_ps](_mm_permute_ps.md) | shuffle | [_mm_permute_ps.c](../../../src/example/avx/_mm_permute_ps.c) |
| [_mm_permutevar_pd](_mm_permutevar_pd.md) | shuffle | [_mm_permutevar_pd.c](../../../src/example/avx/_mm_permutevar_pd.c) |
| [_mm_permutevar_ps](_mm_permutevar_ps.md) | shuffle | [_mm_permutevar_ps.c](../../../src/example/avx/_mm_permutevar_ps.c) |
| [_mm_sllv_epi32](_mm_sllv_epi32.md) | shift left | [_mm_sllv_epi32.c](../../../src/example/avx/_mm_sllv_epi32.c) |
| [_mm_sllv_epi64](_mm_sllv_epi64.md) | shift left | [_mm_sllv_epi64.c](../../../src/example/avx/_mm_sllv_epi64.c) |
| [_mm_srav_epi32](_mm_srav_epi32.md) | shift right | [_mm_srav_epi32.c](../../../src/example/avx/_mm_srav_epi32.c) |
| [_mm_srlv_epi32](_mm_srlv_epi32.md) | shift right | [_mm_srlv_epi32.c](../../../src/example/avx/_mm_srlv_epi32.c) |
| [_mm_srlv_epi64](_mm_srlv_epi64.md) | shift right | [_mm_srlv_epi64.c](../../../src/example/avx/_mm_srlv_epi64.c) |
| [_mm_testc_pd](_mm_testc_pd.md) | test cf | [_mm_testc_pd.c](../../../src/example/avx/_mm_testc_pd.c) |
| [_mm_testc_ps](_mm_testc_ps.md) | test cf | [_mm_testc_ps.c](../../../src/example/avx/_mm_testc_ps.c) |
| [_mm_testnzc_pd](_mm_testnzc_pd.md) | test not cf & zf | [_mm_testnzc_pd.c](../../../src/example/avx/_mm_testnzc_pd.c) |
| [_mm_testnzc_ps](_mm_testnzc_ps.md) | test not cf & zf | [_mm_testnzc_ps.c](../../../src/example/avx/_mm_testnzc_ps.c) |
| [_mm_testz_pd](_mm_testz_pd.md) | test z | [_mm_testz_pd.c](../../../src/example/avx/_mm_testz_pd.c) |
| [_mm_testz_ps](_mm_testz_ps.md) | test z | [_mm_testz_ps.c](../../../src/example/avx/_mm_testz_ps.c) |
