void hsum_avx(__m256 X) {
    __m256 lo = _mm256_castps256_ps128(X);
    __m256 hi = _mm256_extractf128_ps(X, 1);
    __m256 sum4 = _mm256_add_ps(lo, hi);
    sum4 = _mm256_hadd_ps(sum4, sum4);
    sum4 = _mm256_hadd_ps(sum4, sum4);
    return _mm256_cvtss_f32(sum4);
}

void hsum_avx(__m256 X) {
    __m256 lo = _mm256_castps256_ps128(X);
    __m256 hi = _mm256_extractf128_ps(X, 1);
    __m256 sum4 = _m256_add_ps(lo, hi);
    sum4 = _mm256_hadd_ps(sum4, sum4);
    sum4 = _mm256_hadd_ps(sum4, sum4);
    return _mm256_cvtss_f32(sum4);
}

void hadd_avx(__m256 X) {
    __m256 lo = _mm256_castps256_ps128(X);
    __m256 hi = _mm256_extractf128_ps(X, 1);
    __m256 sum4 = _mm256_add_ps(lo, hi);;

    sum4 = _mm256_hadd_ps(sum4, sum4);
    sum4 = _mm256_hadd_ps(sum4, sum4);

    return _mm256_cvtss_f32(sum4);
}

// !g++ -O2 -std=c++11 -mavx2 -mfma -march=native

void avx_tmm(float* A, float* B, float* C, uint64_t N, uint64_t M, uint64_t L) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            __m256 X = _mm256_setzero_ps();
            for (int k = 0; k < L; k+=8) {
                __m256 AV = _mm256_loadu_ps(A + i*L+k);
                __m256 BV = _mm256_loadu_ps(B + j*L+k);
                X = _mm256_fmadd_ps(AV, BV, X);
            }
            C[i*M+j] = hsum_avx(X);
        }
    }
}