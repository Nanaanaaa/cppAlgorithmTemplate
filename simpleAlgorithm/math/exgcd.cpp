std::array<int, 3> exgcd(int a, int b) {
    if (b == 0) {
        return { a, 1, 0 };
    }
    auto [g, x, y] = exgcd(b, a % b);
    return { g, y, x - a / b * y };
}