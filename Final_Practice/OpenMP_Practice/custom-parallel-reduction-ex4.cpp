/*
#include <iostream>
#include <omp.h>

template <typename value_t>
struct binop {
    static constexpr value_t neutral = 0;
    value_t operator()(const value_t &lhs, const value_t &rhs) {
        return (std::abs(lhs) > std::abs(rhs)) ? lhs : rhs;
    }
};

int main() {
    int64_t result = binop<int64_t>::neutral;

    #pragma omp declare reduction(custom_op : int64_t : omp_out = binop<int64_t>(omp_out, omp_in))
    initializer(omp_priv = binop<int64_t>::neutral)

    #pragma omp parallel for reduction(custom_op:result)
    for ...
}
*/