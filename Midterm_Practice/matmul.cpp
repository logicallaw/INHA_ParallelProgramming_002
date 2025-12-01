// 강의 노트 틀린 부분 수정한 버전(n->m)
void matmul(float* A, float* B, float* C, int n, int m, int l) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            float accum = 0;
            for (int k = 0; k < l; k++) {
                accum += A[i*l + k] * B[k*m+j];
            }
            C[i*m+j] = accum;
        }
    }
}