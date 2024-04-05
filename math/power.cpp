template<class T>
constexpr T power(T a, i64 b) {
    T res{ 1 };
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
