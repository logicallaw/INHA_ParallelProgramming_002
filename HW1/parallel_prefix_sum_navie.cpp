#include <stdio.h>
#include <math.h>
#include <omp.h>

void parallel_prefix_sum(int *A, int n) {
    int i, j;
    int *reg = (int *) malloc(n * sizeof(int));

#pragma omp parallel for private(j)
    for (j = 0; j < n; j++) {
        reg[j] = A[j];
    }

    for (i = 0; i < ceil(log2(n)); i++) {
#pragma omp parallel for private(j)
        for (j = (int) pow(2, i); j < n; j++) {
            reg[j] = A[j] + A[j - (int) pow(2, i)];
        }

#pragma omp parallel for private(j)
        for (j = 0; j < n; j++) {
            A[j] = reg[j];
        }
    }

    free(reg);
}


int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(A) / sizeof(A[0]);

    parallel_prefix_sum(A, n);

    printf("Prefix sum result:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}