template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    int sgn = 1;
    if (b < 0) {
        sgn *= -1;
        b *= -1;
    }
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return sgn == -1 ? 1 / res : res;
}