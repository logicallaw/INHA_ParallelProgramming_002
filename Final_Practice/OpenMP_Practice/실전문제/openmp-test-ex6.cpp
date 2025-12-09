double ke, total_energy = 0.0; 

for (i = 0; i < N; i++) {
    ke = 0.5 * mass[i] * velocity[i] * velocity[i];
    
    total_energy += ke;
}

// 위 코드에 #pragma omp parallel for ...를 적용할 때, 괄호 안에 들어가야 할 필수 절(Clause)들을 모두 포함하여 완성된 지시어를 작성하세요.

/*
#pragma omp parallel for private(ke) reduction(+:total_energy)
*/