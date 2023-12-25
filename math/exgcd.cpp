i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) {
        return std::array<i64, 3>{ a, 1, 0 };
    }
    auto [g, x, y] = exgcd(b, a % b);
    return { g, y, x - a / b * y };
}