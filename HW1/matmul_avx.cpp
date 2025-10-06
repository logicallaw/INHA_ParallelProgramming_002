#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <immintrin.h>

using namespace std;


void init(float* A, int n, int m, bool zero) {
    for (int i = 0; i < n * m; i++) {
        A[i] = zero ? 0 : rand() / float(RAND_MAX);
    }
}

float hsum_avx(__m256 X) {
    __m128 lo = _mm256_castps256_ps128(X);
    __m128 hi = _mm256_extractf128_ps(X, 1);
    __m128 sum4 = _mm_add_ps(lo, hi);

    sum4 = _mm_hadd_ps(sum4, sum4);
    sum4 = _mm_hadd_ps(sum4, sum4);

    return _mm_cvtss_f32(sum4);
}

void avx2_tmm(float* A, float* B, float* C,
  uint64_t N) {
    for (uint64_t i = 0; i < N; i++) {
        for (uint64_t j = 0; j < N; j++) {
            __m256 X = _mm256_setzero_ps();
            for (uint64_t k = 0; k < N; k += 8) {
                const __m256 AV = _mm256_loadu_ps(A + i * N + k);
                const __m256 BV = _mm256_loadu_ps(B + j * N + k);
                X = _mm256_fmadd_ps(AV, BV, X);
            }
            C[i * N + j] = hsum_avx(X);
        }
    }
}

int main() {
    int n = 1024;
    float* A = new float[n * n];
    float* B = new float[n * n];
    float* C = new float[n * n];

    init(A, n, n, false);
    init(B, n, n, false);
    init(C, n, n, true);

    auto start = chrono::high_resolution_clock::now();

    avx2_tmm(A, B, C, n);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Execution time: " << diff.count() << " s" << endl;
    cout << "C[0][0]: " << C[0] << endl;

    delete[] A;
    delete[] B;
    delete[] C;
}