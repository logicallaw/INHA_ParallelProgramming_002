#include <iostream>
#include <omp.h>

int main() {
    int i, val = -1;

    #pragma omp parallel for num_threads(2) lastprivate(i, val) schedule(static)
    for (int k = 0; k < 6; ++k) {
        i   = k;
        val = 10 + k;
    }

    std::cout << "i   = " << i   << std::endl;
    std::cout << "val = " << val << std::endl;
}

/*
i   = 5
val = 15
*/