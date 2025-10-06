/*
Execution time: 1.28968 s
C[0][0]: 250.713
*/
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

void matmul(float* A, float* B, float* C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float accum = 0;
            for (int k = 0; k < n; k++) {
                accum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = accum;
        }
    }
}

void init(float* A, int n, int m, bool zero) {
    for (int i = 0; i < n * m; i++) {
        A[i] = zero ? 0 : rand() / float(RAND_MAX);
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

    matmul(A, B, C, n);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Execution time: " << diff.count() << " s" << endl;
    cout << "C[0][0]: " << C[0] << endl;

    delete[] A;
    delete[] B;
    delete[] C;
}