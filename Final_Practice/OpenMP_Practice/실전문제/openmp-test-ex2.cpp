#include <iostream>
#include <omp.h>

int main() {
    int x = 2;   
    int y = 0;  
    
    #pragma omp parallel for num_threads(3) \
            firstprivate(x) lastprivate(y) schedule(static, 2)
    for (int k = 0; k < 9; ++k) {
        x++;           
        y = x + k;     
    }

    std::cout << "y = " << y << std::endl;
}

/*
y = 13
*/