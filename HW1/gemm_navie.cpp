#include <iostream>
using namespace std;

void printMatrix(float* M, int n) {
    cout << "== Matrix ==" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << "== End ==" << endl;
}

void init(float* M, int n, bool zero) {
    for (int i = 0; i < n * n; i++) {
        M[i] = zero ? 0 : rand() / float(RAND_MAX);
    }
}

void matmul(float* A, float* B, float* C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float tmp = 0;
            for (int k = 0 ;k < n; k++) {
                tmp += A[i * n + k] * B[k + n * j];
            }
            C[i * n + j] = tmp;
        }
    }
}

int main() {
    int n = 4;

    float* A = new float[n * n];
    float* B = new float[n * n];
    float* C = new float[n * n];

    init(A, n, false);
    init(B, n, false);
    init(C, n, true);

    matmul(A, B, C, n);
}