template<class T>
constexpr T power(T base, i64 exp) {
    T res{ 1 };
    for (; exp; exp /= 2, base *= base) {
        if (exp % 2) {
            res *= base;
        }
    }
    return res;
}
