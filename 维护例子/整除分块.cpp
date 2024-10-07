i64 sum = 0;
// 注意右端点不能大于n
for (i64 l = 1; l <= n; l++) {
    i64 d = n / l, r = std::min(n, n / d);
    sum += i64(r - l + 1) * d;
    l = r;
}