#include <cstdlib>
void matmul(float* A, float* B, float* C, int N, int M, int L) {
    float* Bt = new float[N*M];
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < M; j++) {
            Bt[j*L+i] = B[i*M + j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            float accum = 0;
            for (int k = 0; k < L; k++) {
                accum += A[i*L + k] * Bt[j*L + k];
            }
            C[i*M+j] = accum;
        }
    }
}

float* init(float* A, int N, int M, bool zero) {
    // for(int i = 0; i < N; i++) {
    //     for(int j = 0; j < N; j++) {
    //         A[i*N+j] = (zero) ? 0 : rand() / float(RAND_MAX);
    //     }
    // }
    for (int i = 0; i < N*M; i++) {
        A[i] = (zero) ? 0 : rand() / float(RAND_MAX);
    }
}