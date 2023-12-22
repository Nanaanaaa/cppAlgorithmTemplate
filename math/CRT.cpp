std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) {
        return { a, 1, 0 };
    }
    auto [g, x, y] = exgcd(b, a % b);
    return { g, y, x - a / b * y };
}

i64 CRT(const std::vector<std::array<int, 2>>& info) {
    i64 M = 1, res = 0;
    for (const auto [a, m] : info) {
        M *= m;
    }
    for (const auto [a, m] : info) {
        auto [g, x, y] = exgcd(M / m, m);
        res = ((res + M / m * x * a) % M + M) % M;
    }
    return res;
}