#include <stdio.h>
#define SDIV(x, y) ((x + y - 1) / y)

template <typename index_t, typename value_t, uint32_t chunk_size = 8>
__global__ void shared_covariance_kernel(
   value_t *Data, value_t *Cov, index_t num_entries, index_t num_features) {
    const index_t base_x = blockIdx.x * chunk_size;
    const index_t base_y = blockIdx.y * chunk_size;

    const index_t thid_x = threadIdx.x;
    const index_t thid_y = threadIdx.y;

    const index_t x = base_x + thid_x;
    const index_t y = base_y + thid_y;

    if (base_x >= base_y + chunk_size) return;

    __shared__ value_t cache_x[chunk_size][chunk_size];
    __shared__ value_t cache_y[chunk_size][chunk_size];

    const index_t num_chunks = SDIV(num_entries, chunk_size);

    value_t accum = 0;

    for (index_t chunk = 0; chunk < num_chunks; chunk++) {
        const index_t row = thid_y + chunk * chunk_size;
        const index_t col_x = thid_x + base_x;
        const index_t col_y = thid_y + base_y;

        const bool valid_row = row < num_entries;
        const bool valid_col_x = col_x < num_features;
        const bool valid_col_y = col_y < num_features;

        cache_x[thid_y][thid_x] = valid_row * valid_col_x ? Data[row * num_features + col_x] : 0;
        cache_y[thid_y][thid_x] = valid_row * valid_col_y ? Data[row * num_features + col_y] : 0;
        __syncthreads();

        if (x <= y) {
            for (index_t k = 0; k < chunk_size; k++) {
                accum += cache_y[k][thid_y] * cache_x[k][thid_x];
            }
        }
        __syncthreads();
    }

    if (y < num_features && x <= y) {
        Cov[y * num_features + x] = Cov[x * num_features + y] = accum / num_entries;
    }
}


