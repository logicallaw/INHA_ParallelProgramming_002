
/* 나의 정답
template <typename value_t>
struct max_size_t_op {
    static constexpr value_t neutral = 0;
    
    value_t operator() (value_t &lhs, value_t &rhs) {
        return (lhs > rhs) ? lhs : rhs;
    }
};

int main() {
    std::size_t max_len = 0;
    max_size_t_op<std::size_t> myMax;

    #pragma omp declare reduction( \
        myMax : std::size_t : \
        omp_out = max_size_t<value_t>()(omp_out, omp_in)
    )
    initializer(omp_priv = max_size_t_op<std::size_t>::neutral)

    std::vector<std::size_t> vec;
    vec.assign(100, 0);

    #pragma omp parallel for reduction(myMax:max_len)
    for (std::size_t i = 0; i < vec.size(); i++) {
        std::size_t len = vec[i].size();
        max_len = (len > max_len) ? len : max_len;
    }

    std::cout << max_len << std::endl;

    return 0;
}
*/

/* 틀린 부분
omp_out 부분에서 value_t가 아닌 std::size_t가 맞음.
*/

/* 개선

int main() {
    std::size_t max_len = max_size_t<std::size_t>::neutral;
    std::vector<std::size_t> vec;
    vec.assign(100, 0);
    
    #pragma omp declare reduction( \
        custom_op : std::size_t : \
        omp_out = max_size_t<std::size_t>()(omp_out, omp_in)
    )
    initializer(omp_priv = max_size_t_op<std::size_t>::neutral)

    #pragma omp parallel for reduction(custom_op:max_len)
    for (std::size_t i = 0; i < vec.size(); i++) {
        std::size_t len = vec[i].size();
        max_len = (len > max_len) ? len : max_len;
    }

    std::cout << max_len << std::endl;

    return 0;
}
*/