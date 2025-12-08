/* 
### 문제: 가장 높은 점수를 가진 학생 찾기 (Top Ranker Reduction)

다음 `Student` 구조체 배열이 주어집니다. OpenMP의 **User Defined Reduction**을 사용하여 아래 조건에 맞는 \*\*"1등 학생의 정보(객체 자체)"\*\*를 `best_student` 변수에 구하는 코드를 완성하세요.

#### **조건**

1.  **비교 로직 (Combiner):**
      * `score`가 더 높은 학생을 선택합니다.
      * 만약 `score`가 같다면, `id`가 **더 작은** 학생을 선택합니다. (오름차순 우선)
2.  **초기값 (Initializer):**
      * 비교를 시작하기 위한 항등원(Neutral Value)으로 `id = -1`, `score = -1`을 사용하세요.
3.  **지시어:**
      * `#pragma omp declare reduction`을 사용하여 `myMax`라는 이름의 리덕션을 정의하세요.
      * `#pragma omp parallel for` 구문에서 정의한 `myMax`를 사용하세요.

-----

### **작성해야 할 코드 (빈칸 채우기)**

아래 코드에서 `// TODO 1`과 `// TODO 2` 부분을 직접 작성해보세요.

```cpp
#include <iostream>
#include <vector>
#include <omp.h>

struct Student {
    int id;
    int score;
};

int main() {
    // 100명의 학생 데이터 생성 (임의 설정)
    std::vector<Student> students(100);
    for(int i=0; i<100; ++i) {
        students[i] = {i, i % 40}; // 점수는 0~39 반복
    }
    // 예외 케이스: 50번 학생에게 압도적인 점수 부여
    students[50].score = 100;
    
    // 결과를 담을 변수 (초기값 설정)
    Student best_student = {-1, -1};

    // ---------------------------------------------------------
    // [문제 1] declare reduction 지시어를 작성하세요.
    // 이름: myMax, 타입: Student
    // ---------------------------------------------------------
    // TODO 1: #pragma omp declare reduction ... 
    
    


    // ---------------------------------------------------------
    // [문제 2] parallel for와 reduction 절을 사용하여 루프를 실행하세요.
    // ---------------------------------------------------------
    // TODO 2: #pragma omp ...
    for (int i = 0; i < 100; i++) {
        // (힌트: reduction 내부 로직은 선언부에서 처리되므로, 
        //  루프 안에서는 일반적인 비교/대입 처럼 작성하거나, 
        //  혹은 OpenMP reduction이 적용되도록 변수를 업데이트하는 형태여야 함)
        
        // 하지만 커스텀 리덕션을 쓸 때는 루프 바디가 조금 특이해질 수 있습니다.
        // 여기서는 직관적으로 "best_student와 students[i]를 비교해서 업데이트" 하는
        // 로직을 리덕션이 알아서 처리하게끔 유도해야 합니다.
        // 시험에서는 보통 아래와 같이 리덕션 대상 변수에 계속 병합을 시도하는 형태로 씁니다.
        
        if (students[i].score > best_student.score || 
           (students[i].score == best_student.score && students[i].id < best_student.id)) {
            best_student = students[i];
        }
    }

    std::cout << "Best Student ID: " << best_student.id 
              << ", Score: " << best_student.score << std::endl;

    return 0;
}
```

-----

### **Tip (풀이 전 체크포인트)**

1.  **Combiner (`omp_out = ...`)**: `omp_out`이 기존에 확보된 값, `omp_in`이 새로 들어온 값(또는 다른 스레드의 값)입니다. 삼항 연산자(`? :`)나 `if` 문을 사용해서 `omp_out`을 갱신해야 합니다.
2.  **Initializer**: `omp_priv`를 어떻게 초기화할지 `initializer(...)` 안에 적어야 합니다.
*/

/* 나의 정답
#pragma omp declare reduction( \
  myMax : Student : \
  omp_out = (omp_out.score != omp_in.score) ?
    ((omp_out.score > omp_in.score) ? omp_out : omp_in) : 
    ((omp_out.id < omp_in.id) ? omp_out : omp_in)
    )
)
initialize(omp_priv=Student(-1, -1))

#pragma omp parallel for reduction(myMax:best_student)
*/

/* 틀린 부분
initialize -> initializer

Student(-1, 1)은 해당 생성자 정의되어 있지 않아서 에러 발생. -> {-1, -1})
*/