#include <stdio.h>

__global__ void kernel() {
    printf("Hello from thread (%u %u % u) \n"
        "in a block of dimension (%u %u %u) \n"
        "with block identifier (%u %u %u) \n"
        "spawned in a grid of shape (%u %u %u) \n",
        threadIdx.x, threadIdx.y, threadIdx.z,
        blockDim.x, blockDim.y, blockDim.z,
        blockIdx.x, blockIdx.y, blockIdx.z,
        gridDim.x, gridDim.y, gridDim.z);
}

int main() {
    cudaSetDevice(0);

    dim3 grid_dim(2, 2, 1);
    dim3 block_dim(3, 3, 1);

    kernel<<<grid_dim, block_dim>>>();

    cudaDeviceSynchronize();

    return 0;
}