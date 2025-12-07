#include <iostream>
#include <omp.h>

int main() {
#pragma omp for
	for (int i = 0; i < 10; i++) {
		std::cout << omp_get_num_threads() << std::endl;
		std::cout << omp_get_thread_num() << std::endl;
	}
}
