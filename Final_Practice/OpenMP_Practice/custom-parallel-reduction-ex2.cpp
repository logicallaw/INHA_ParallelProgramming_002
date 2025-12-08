/*
문제 1. 절댓값이 가장 큰 원소 찾기 (값만)

목표

배열 a[]에서 절댓값이 가장 큰 원소를 찾는 프로그램을, 사용자 정의 reduction 으로 병렬화하라.

상세 조건
	•	타입은 double.
	•	여러 개가 절댓값 최대를 가지면 어느 하나여도 상관 없음.
	•	reduction 연산은 “두 값 중 절댓값이 더 큰 쪽을 반환하는 이항 연산”이어야 한다.
	•	neutral element는 “절댓값 기준으로 결과에 영향을 주지 않는 값”을 고안해서 사용하라.

Serial 코드 스케치

double max_abs = 0.0;
for (size_t i = 0; i < n; ++i) {
    double v = a[i];
    if (std::abs(v) > std::abs(max_abs)) {
        max_abs = v;
    }
}
std::cout << max_abs << '\n';

해야 할 일
	1.	template <typename T> struct max_abs_op { ... }; 같은 functor 정의
	2.	neutral 정의
	3.	operator()(lhs, rhs)에서 어떤 값을 반환할지 정의
	4.	#pragma omp declare reduction( ... ) initializer(...) 작성
	5.	#pragma omp parallel for reduction(사용자연산:max_abs) 로 루프 병렬화

⸻

문제 2. 절댓값이 가장 큰 원소의 “값 + 인덱스” 모두 찾기

목표

배열 a[]에서 절댓값이 가장 큰 원소의 값과 인덱스를 동시에 찾는 사용자 정의 reduction을 작성하라.

상세 조건
	•	배열: std::vector<double> a(n);
	•	reduction 대상 타입은 아래 구조체:

struct MaxAbsElem {
    double value;   // 원소 값
    std::size_t idx; // 인덱스
};


	•	비교 기준: std::abs(value)가 더 큰 쪽을 “더 큰” 것으로 본다.
	•	절댓값이 같으면 더 작은 인덱스를 선택하라. (tie-breaking 조건)
	•	neutral element는 직접 설계: “아무 실제 원소보다 항상 패배하는” 값 + 인덱스 조합.

Serial 코드 스케치

MaxAbsElem best{0.0, 0}; // 초기화는 실제 로직에 맞게 조정 필요
for (size_t i = 0; i < n; ++i) {
    double v = a[i];
    double best_abs = std::abs(best.value);
    double cur_abs  = std::abs(v);
    if (cur_abs > best_abs || (cur_abs == best_abs && i < best.idx)) {
        best.value = v;
        best.idx   = i;
    }
}
std::cout << "value=" << best.value << " idx=" << best.idx << '\n';

해야 할 일
	1.	MaxAbsElem에 대해 작동하는 functor struct max_abs_elem_op { ... }; 정의
	2.	neutral element를 static constexpr MaxAbsElem neutral; 등으로 구현
	3.	declare reduction 문 작성
	4.	병렬 루프에서 MaxAbsElem을 reduction 변수로 사용

⸻

문제 3. 문자열 길이의 최대값 찾기 (커스텀 타입 + non-trivial neutral)

목표

std::vector<std::string> 안에서 가장 긴 문자열의 길이를 사용자 정의 reduction으로 계산하라.

상세 조건
	•	reduction 대상 타입: std::size_t (길이)
	•	연산: 두 길이 중 더 큰 값을 선택한다.
	•	neutral element: 0 (길이로서 중립적)
	•	단, 실제 루프 안에서는 매번 str.size()를 바로 비교하지 않고,
아래와 같이 “직접 연산으로 갱신”되도록 작성하라.

Serial 코드 스케치

std::size_t max_len = 0;
for (std::size_t i = 0; i < vec.size(); ++i) {
    std::size_t len = vec[i].size();
    if (len > max_len) {
        max_len = len;
    }
}
std::cout << max_len << '\n';

해야 할 일
	1.	template <typename T> struct max_op; 또는 struct max_size_t_op; 정의
	2.	neutral = 0
	3.	declare reduction(maxlen : std::size_t : ...) initializer(...)
	4.	#pragma omp parallel for reduction(maxlen:max_len) 로 병렬화

(이 문제는 구조 자체는 간단하지만, “내장 reduction(max: var) 대신 직접 정의”하는 연습)

⸻

문제 4. 부호 있는 합계: 절댓값 기준으로 가장 큰 “부분합” 찾기

조금 응용된 문제입니다.

목표

정수 배열 a[]에 대해, 모든 원소의 합을 구하는 게 아니라,
각 스레드의 부분합 중에서 절댓값이 가장 큰 부분합을 찾는 사용자 정의 reduction을 작성하라.

상세 조건
	•	타입: int64_t
	•	각 스레드는 자신이 담당한 구간에 대해 local_sum += a[i]; 로 부분합을 만든다.
	•	reduction 시에는 “두 부분합 중 절댓값이 더 큰 쪽”을 선택한다.
	•	결과: “가장 큰 절댓값을 갖는 부분합 값” 하나 (int64_t)를 출력.
	•	neutral element: 0

Serial 코드 스케치(의미 설명용)

// 실제로는 이렇게 돌리면 전체 합만 나오지만,
// 우리는 "부분합 중 절댓값이 가장 큰 값"을 찾는 reduction을 설계하는 것.
int64_t result = 0;
int64_t local_sum = 0;
for (size_t i = 0; i < n; ++i) {
    local_sum += a[i];
    // 여러 스레드가 있다면 각자의 local_sum을 reduction으로 모을 때
    // |local_sum|이 가장 큰 것을 고르는 사용자 정의 연산을 만든다고 생각하면 됨.
}

해야 할 일
	1.	struct max_abs_sum_op { static constexpr int64_t neutral = 0; int64_t operator()(int64_t lhs, int64_t rhs) const; };
	2.	declare reduction(max_abs_sum : int64_t : ...) initializer(...)
	3.	병렬 루프 안에서 local_sum을 계산하고, 루프 바깥의 result에 대해 reduction(max_abs_sum: result)를 적용하도록 전체 구조를 설계

(이 문제의 포인트는 “스레드 로컬 상태(local_sum) + reduction 대상(result)을 어떻게 연결할 것인가”를 고민해 보는 것)

*/
/* 나의 풀이
struct max_abs_op {
    constexpr double neutral = 0.0;

    double operator()(double a,double b) {
        if (std::abs(a) > std::abs(b)) {
            return a;
        }
        return b;
    }
}

int main() {
    max_abs_op myMax;

    #pragma omp declare reduction( \
        myMax : double : \
        omp_out = myMax(omp_out, omp_in)
    )
    initializer(max_abs_op::neutral)

    double max_abs = 0.0;

    #pragma omp parallel for reduction(myMax:max_abs)
    for (size_t i = 0; i < n; i++) {
        double v = a[i];
        if (myMax(v, max_abs)) {
            max_abs = v;
        }
    }
    std::cout << max_abs << "\n";
}
*/

/* 틀린 부분
constexpr double neutral = 0.0; -> static constexpr double neutral = 0.0;
struct에 세미콜론 빠짐 -> struct ... {};
declare reduction에서 omp_out을 정의할 때, myMax 아닌 max_abs_op()(omp_out, omp_in)으로 정의하기
myMax는 bool을 반환하지 않음. -> max_abs = max_abs_op()(max_abs, v);
*/