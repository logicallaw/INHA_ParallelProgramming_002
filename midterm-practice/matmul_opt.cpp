// 강의노트 틀린 부분 수정한 버전(n -> m)
#include <cstdlib>

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

void matmul(float* A, float* B, float* C, int n, int m, int l) {
    float* Bt = new float[n*m];
    init(Bt, n, m, true);

    for(int i = 0; i < l; i++) {
        for(int j = 0; j < m; j++) {
            Bt[j*l+i] = B[i*m+j];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            float accum = 0; 
            for(int k = 0; j < l; k++) {
                accum += A[i*l+k] * Bt[j*l+k];
            }
            C[i*m+j] = accum;
        }
    }
}
