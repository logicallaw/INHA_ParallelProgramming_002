#include <stdio.h>

__global__ void hello_kernel() {
    const int thid = blockDim.x * blockIdx.x + threadIdx.x;
    printf("Hello from thread %d\n", thid);
}

int main(int argc, char *argv[]) {
    cudaSetDevice(0);

    hello_kernel<<<1, 4>>>();

    cudaDeviceSynchronize();
}