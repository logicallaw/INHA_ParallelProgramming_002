#include <stdio.h>
#include <cmath>

template <typename index_t, typename value_t> __host__
value_t plain_dtw(value_t *query, value_t *subject, index_t num_features) {
	const index_t lane = num_features + 1;
	value_t *penalty = new value_t[lane * lane];
	for (index_t index = 1; index < lane; index++) {
		penalty[index] = penalty[index * lane] = INFINITY;
	}
	penalty[0] = 0;
	for (index_t row = 1; row < lane; row++) {
		const value_t q_value = query[row - 1];
		for (index_t col = 1; col < lane; col++) {
			const value_t diag = penalty[(row - 1) * lane + col - 1];
			const value_t abve = penalty[(row - 1) * lane + col + 0];
			const value_t left = penalty[(row + 0) * lane + col - 1];
			
			const value_t residue = q_value - subject[col - 1];
			penalty[row * lane + col] = residue * residue + std::min(diag, std::min(abve, left));
		}
	}
	const value_t result = penalty[lane * lane - 1];
	delete[] penalty;

	for (index_t i = 0; i < lane; i++) {
		for (index_t j = 0; j < lane; j++) {
			printf("%f ", penalty[i * lane + j]);
		}
		printf("\n");
	}
	return result;
}

int main() {
	float query[]= {1, 2, 4, 1};
	float subject[] = {1, 5, 4, 2};
	float result = plain_dtw(query, subject, 4);

	printf("result: %f", result);

	return 0;
}
