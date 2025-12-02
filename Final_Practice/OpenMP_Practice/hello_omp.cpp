#include <iostream>
#include <omp.h>

int main() {
    // 시스템의 프로세서(코어) 수를 가져옵니다.
    int num_procs = omp_get_num_procs();
    std::cout << "시스템의 프로세서 수: " << num_procs << std::endl;

    // 가져온 코어 수만큼 스레드를 생성하여 병렬 영역을 시작합니다.
    #pragma omp parallel num_threads(num_procs)
    {
        // 각 스레드의 고유 ID를 가져옵니다.
        int thread_id = omp_get_thread_num();
        
        // 스레드 ID와 함께 메시지를 출력합니다.
        // std::cout은 스레드에 안전하지 않으므로, 출력이 섞이지 않도록 critical 섹션으로 보호합니다.
        #pragma omp critical
        {
            std::cout << "Hello from thread " << thread_id << std::endl;
        }
    }

    return 0;
}

