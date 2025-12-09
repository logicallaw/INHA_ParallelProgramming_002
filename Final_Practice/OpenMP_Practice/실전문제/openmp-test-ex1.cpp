// 강추 문제
#include <iostream>
#include <omp.h>

int main() {
    int state = 0;     
    int total = 20;   

    #pragma omp parallel for num_threads(3) \
            firstprivate(state) reduction(+:total) schedule(static, 2)
    for (int i = 0; i < 8; ++i) {

        state += i; 

        total += state; 
    }

    std::cout << "total = " << total << std::endl;
    return 0;
}

/*
total = 62
*/