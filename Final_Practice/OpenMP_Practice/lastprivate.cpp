#include <omp.h>
#include <cstdio>
#include <vector>

int main() {
	int i = 10;

#pragma omp parallel for lastprivate(i)
	for (int j = 0; j < 20; j++) {
		printf("i: %d\n", i);
	}

	printf("current i: %d\n", i);
}

