#include <iostream>
void matmul(float* A, float* B, float* C, uint64_t N, uint64_t M, uint64_t L) {
    for (uint64_t i = 0; i < N; i++) {
        for (uint64_t j = 0; j < M; j++) {
            float accum = 0;
            for (uint64_t k = 0; k < L; k++) {
                accum += A[i*L+k] * B[k*M+j];
            }
            C[i*M+j] = accum;
        }
    }
}