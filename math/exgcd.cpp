i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}