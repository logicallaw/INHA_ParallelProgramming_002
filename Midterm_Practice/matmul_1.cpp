void matmul(float* A, float* B, float* C, int M, int N, int L) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            float accum = 0;
            for (int k = 0; k < L; k++) {
                accum += A[i*L + k] * B[k*M + j];
            }
            C[i*M + j] = accum;
        }
    }
}