#include <omp.h>
#include <cstdio>
#include <vector>

int main() {
	int max_outside = omp_get_max_threads();
	int num_outside = omp_get_num_threads();
        printf("병렬 밖의 설정값(Max): %d, 병렬 밖의 설정값(Num): %d\n", max_outside, num_outside);

# pragma omp parallel
	{
		int max_inside = omp_get_max_threads();
		int num_inside = omp_get_num_threads();

		printf("설정값(Max): %d, 현재인원(Num): %d\n", max_inside, num_inside);
	}
}
