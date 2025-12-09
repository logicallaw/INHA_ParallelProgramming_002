int idx; 

for (i = 0; i < num_data; i++) {
    idx = calculate_bin_index(data[i]); 
    
    histogram[idx]++; 
}

// 위 코드를 병렬화하기 위해 for문 위에 적어야 할 지시어는 무엇인가요?

/*
#pragma omp parallel for private(idx)
for (i = 0; i < num_data; i++) {
    idx = calculate_bin_index(data[i]); 
    
    #pragma omp atomic 
    histogram[idx]++; 
}
*/