std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) {
        return { a, 1, 0 };
    }
    auto [g, x, y] = exgcd(b, a % b);
    return { g, y, x - a / b * y };
}

bool merge(i64& a, i64& b, i64 c, i64 d) {
    auto [g, x, y] = exgcd(b, d);
    if ((c - a) % g) {
        return false;
    }
    d /= g;
    i64 t0 = (__int128(c - a) / g % d * x % d + d) % d;
    a = b * t0 + a;
    b = b * d;
    return true;
}

i64 exCRT(const std::vector<std::array<i64, 2>>& info) {
    i64 a = 0, b = 1; // x mod b == a
    for (auto [c, d] : info) {
        if (!merge(a, b, c, d)) {
            return -1;
        }
    }
    return a;
}