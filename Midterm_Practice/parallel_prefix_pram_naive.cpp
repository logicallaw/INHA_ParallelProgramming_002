// 문제의 크기는 n
// 프로세서는 p개

for (j = 0; j < n; j++) {
    reg_j = A[j]; // O()
}

for (i = 0; i < ceil(log(n)); i++) {
    for (j = pow(2, i); j < n; j++) {
        reg_j += A[j - pow(2, i)];
        A[j] = reg_j;
    }
}

C(n) = T(n, p) x p = O(log n) x n = O(n log n)
즉, 이 알고리즘의 Cost(Time complexity 계산한게 아님)는 O(n log n)이다.

// == 내가 생각하기 올바른 버전은...
// 각 프로세서 로컬 레지스터에 값을 저장하는데,
// 저장된 값을 실제로 읽어오는 프로세서는 1번 프로세서부터이므로

// 0->1로 수정함.
for (j = 1; j < n; j++) {
    reg_j = A[j];
}

for (i = 0; i < ceil(log(n)); i++) {
    for (j = pow(2, i); j < n; j++) {
        reg_j += A[j - pow(2, i)];
        A[j] = reg_j;
    }
}

// 이게 맞다고 생각한다.