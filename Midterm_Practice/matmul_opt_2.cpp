#include <iostream>

void matmul_opt(float* A, float* B, float* C, uint64_t N, uint64_t M, uint64_t L) {
    float* Bt = new float[M*L];

    for (uint64_t i = 0; i < L; i++) {
        for (uint64_t j = 0; j < M; j++) {
            Bt[j*L+i] = B[i*M + j];
        }
    }

    for (uint64_t i = 0; i < N; i++) {
        for (uint64_t j = 0; j < M; j++) {
            float accum = 0;
            for (uint64_t k = 0; k < L; k++) {
                accum += A[i*L + k] * B[j*L + k]; 
            }
            C[i*M+j] = accum;
        }
    }
}