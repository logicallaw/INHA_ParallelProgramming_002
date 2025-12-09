// 응용 문제(어려움)
#include <iostream>
#include <omp.h>

int main() {
    int g_idx = 0;              
    int arr[6] = {-1, -1, -1, -1, -1, -1}; 

    #pragma omp parallel num_threads(3)
    {
        int tid = omp_get_thread_num();
        int count = tid + 1;   
        int start_pos;          
        
        #pragma omp atomic capture
        { start_pos = g_idx; g_idx += count; }
        
        for (int i = 0; i < count; ++i) {
            arr[start_pos + i] = tid * 10 + i;
        }
    }

    for(int i=0; i<6; i++) std::cout << arr[i] << " ";
}

// 위 가정(T1 -> T0 -> T2 진입)대로 실행되었을 때, 배열 arr의 최종 상태(6개 값)는 무엇인가요?

/*
10 11 0 20 21 22
*/