#include <immintrin.h>

// __m256 _mm256_set_zero_ps(void)
// __m256 _mm256_loadu_ps(float const* addr)
// __m256 _mm256_fmadd_ps(__m256 a, __m256 b, __m256 c)

void avx2_tmm(float* A, float* B, float* C,
    uint64_t M, uint64_t L, uint64_t N) {
    // M, L, N은 index
    for(uint64_t i = 0; i < N; i++) {
        for(uint64_t j = 0; j < M; j++) {
            __m256 X = _mm256_setzero_ps();
            for(uint64_t k = 0; k < L; k+=8) {
                const __m256 AV = _mm256_loadu_ps(A + i*L + k);
                const __m256 BV = _mm256_loadu_ps(B + j*L + k);
                X = _mm256_fmadd_ps(AV, BV, X);
            }
            C[i*M + j] = hsum_avx(X);
        }
    }
}

float hsum_avx(__m256 X) {
    __m256 lo = _mm256_castps256_ps128(X);
    __m128 hi = _mm256_extractf128_ps(X, 1);
    __m128 sum4 = _mm_add_ps(lo, hi);
    sum4 = _mm_hadd_ps(sum4, sum4);
    sum4 = _mm_hadd_ps(sum4, sum4);
    return _mm_cvtss_f32(sum4);
}