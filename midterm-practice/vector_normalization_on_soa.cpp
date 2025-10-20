#include <iostream>
#include <immintrin.h>
void avx_soa_norm(float* x, float* y, float* z, uint64_t length) {
    for(uint64_t i = 0; i < length; i+=8) {
        __m256 X = _mm256_loadu_ps(x+i);
        __m256 Y = _mm256_loadu_ps(y+i);
        __m256 Z = _mm256_loadu_ps(z+i);

        __m256 R = _mm256_fmadd_ps(X, X,
            _mm256_fmadd_ps(Y, Y, _mm256_mul_ps(Z, Z)));

        R = _mm256_rsqrt_ps(R);
        _mm256_store_ps(x+i, _mm256_mul_ps(X, R));
        _mm256_store_ps(y+i, _mm256_mul_ps(Y, R));
        _mm256_store_ps(z+i, _mm256_mul_ps(Z, R));
    }
}