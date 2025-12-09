// 강추 문제
#include <iostream>
#include <omp.h>

int main() {
    int count = 5;    
    int sum = 0;      

    #pragma omp parallel for num_threads(2) \
            firstprivate(count) reduction(+:sum) schedule(static, 2)
    for (int i = 0; i < 10; ++i) {
        count++; 

        sum += count; 
    }

    std::cout << "sum = " << sum << std::endl;
    return 0;
}

/*
sum = 81
*/