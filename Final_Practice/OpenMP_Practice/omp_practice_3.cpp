/* 문제 코드
for (i = k; i < n; i++)
  a[i] = b * a[i-k];
*/

/* 내 병렬화 코드
for (index_t i = 0; i < k * (n / k); i++) {
  #pragma omp parallel for
  for (index_t j = i; j < i + k; j++) {
    if (j + k >= n) break;
    a[j + k] = b * a[j];
  }
*/

/* 교수님 병렬화 코드 
#pragma omp parallel for
for (index_t s = 0; s < k; s++) {
  for (index_t i = s + k; i < n; i++) {
    a[i] = b * a[i-k];
  }
}
*/