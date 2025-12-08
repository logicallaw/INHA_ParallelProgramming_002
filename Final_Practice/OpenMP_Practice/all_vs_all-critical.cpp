#include <iostream>
#include <omp.h>

template <typename value_t, typename index_t>
void all_vs_all(
    value_t *test,
    value_t *train,
    value_t *delta,
    index_t num_test,
    index_t num_train,
    index_t num_features,
    bool parallel
) {
    for (index_t i = 0; i < num_test; i++) {
        for (index_t j = 0; j < num_train; j++) {
            value_t accum = 0;
            #pragma omp parallel for
            for (index_t k = 0; k < num_features; k++) {
                #pragma omp critical
                accum += test[i * num_features + k] * train[j * num_features + k];
            }
            delta[i * num_train + j] = accum;
        }
    }
}