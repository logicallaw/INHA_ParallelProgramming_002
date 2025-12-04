#include <stdio.h>

template <typename index_t, typename value_t> __global__
void symmetric_covariance_matrix(
    value_t *Data,
    value_t *Cov,
    value_t num_entries,
    value_t num_features) {
        const auto J = blockDim.x * blockIdx.x + threadIdx.x;
        const auto j = blockDim.y * blockIdx.y + threadIdx.y;

        if (j < num_entries && J <= j) {
            value_t accum = 0;
            for (index_t entry = 0; entry < num_entries; entry++) {
                accum += Data[entry * num_features + j] * Data[entry * num_features + J];
            }
            Cov[j * num_features + J] = Cov[J * num_features + j] = accum;
        }
    }

int main() {
    cudaSetDevice(0);

    int rows = 45;
    int cols = 55;
    int imgs = 202599;
    
    int* Data = new int[imgs * rows * cols];
    int* Cov = new int[rows * cols * rows * cols];

    dim3 blocks(SDIV(rows * cols, 8), SDIV(rows * cols, 8));
    dim3 threads(8, 8);

    symmetric_covariance_matrix<<<blocks, threads>>>(Data, Cov, imgs, rows * cosl);

    cudaDeviceSynchronize();

    return 0;
}