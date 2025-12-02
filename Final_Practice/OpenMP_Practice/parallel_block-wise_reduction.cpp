// reduction_init_demo.cpp
#include <omp.h>
#include <cstdio>
#include <vector>

int main() {
    const int num_features = 32;
    std::vector<int> data(num_features, 1);     // 모두 1

    long long accum = 1000; // 병렬 구간 들어가기 *전*의 원래 값 (눈에 띄게 비영(非0))

    #pragma omp parallel reduction(+:accum)
    {
        int tid = omp_get_thread_num();
        bool first = true;
        int handled = 0;

        #pragma omp single
        {
            std::printf("threads = %d\n", omp_get_num_threads());
        }

        #pragma omp for
        for (int k = 0; k < num_features; ++k) {
            if (first) {
                // 각 스레드가 맡은 첫 반복에서 사본의 초기값을 출력
                #pragma omp critical
                std::printf("[T%02d] initial private accum = %lld\n", tid, accum);
                first = false;
            }
            accum += data[k];   // 스레드 *사본*에 누적
            ++handled;
        }

        // 병합되기 전, 스레드 사본의 최종값을 출력
        #pragma omp critical
        std::printf("[T%02d] private accum after loop = %lld (iters=%d)\n",
                    tid, accum, handled);
    } // ← 여기서 모든 사본이 + 로 병합되어 원래 accum 에 반영됨

    std::printf("Final accum (after merge) = %lld ; expected = 1000 + %d = %d\n",
                accum, num_features, 1000 + num_features);
}
