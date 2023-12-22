constexpr i64 power(i64 a, i64 b, i64 P = ::P) {
    i64 res = 1;
    for (; b; b /= 2, a = a * a % P) {
        if (b % 2) {
            res = res * a % P;
        }
    }
    return res;
}
