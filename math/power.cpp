using i64 = long long;
constexpr i64 power(i64 base, i64 exp) {
    i64 res{ 1 };
    for (; exp; exp /= 2, base = base * base % P) {
        if (exp % 2) {
            res = (res * res % P);
        }
    }
    return res;
}
