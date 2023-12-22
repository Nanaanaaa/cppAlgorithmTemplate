std::vector<int> inv(n + 1, 1);
for (int i = 2; i <= n; i++) {
    inv[i] = i64(P - P / i) * inv[P % i] % P;
}