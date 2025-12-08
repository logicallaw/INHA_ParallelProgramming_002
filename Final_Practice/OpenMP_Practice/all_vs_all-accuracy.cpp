#include <iostream>
#include <omp.h>

using namespace std;

template <typename label_t, typename value_t, typename index_t>
value_t accuracy(
    label_t *label_test,
    label_t *label_train,
    value_t *delta,
    index_t num_test,
    index_t num_train,
    index_t num_features,
    index_t num_classes,
    bool parallel
) {
    index_t counter = index_t(0);
    #pragma omp parallel for reduction(+:counter) if (parallel) 
    for (index_t i = 0; i < num_test; i++) {
        value_t bsf = std::numeric_limits<value_t>::max();
        value_t jst = std::numeric_limits<value_t>::max();
        for (index_t j = 0; j < num_train; j++) {
            const value_t value = delta[i * num_train + j];
            if (value < bsf) {
                bsf = value;
                jst = j;
            }
        }
        bool match = true;
        for (index_t k = 0; k < num_classes; k++) {
            match &= label_test[i * num_classes + k] == label_train[jst * num_classes + k];
        }
        counter += match;
    }
    return value_t(counter) / value_t(num_test);
}