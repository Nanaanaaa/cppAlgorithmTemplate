struct ST {
    std::vector<std::vector<int>> f, g, h;
    ST(int n, int m, std::vector<int> a) : f(n), g(n), h(n) {
        for (int i = 0; i < n; i++) {
            f[i].resize(m), g[i].resize(m), h[i].resize(m);
            f[i][0] = g[i][0] = h[i][0] = a[i];
        }
        for (int j = 1; (1ll << j) < n; j++) {
            for (int i = 0; i + (1ll << j) - 1 < n; i++) {
                f[i][j] = std::max(f[i][j - 1], f[i + (1ll << (j - 1))][j - 1]);
                g[i][j] = std::min(g[i][j - 1], g[i + (1ll << (j - 1))][j - 1]);
                h[i][j] = std::gcd(h[i][j - 1], h[i + (1ll << (j - 1))][j - 1]);
            }
        }
    }
    int askMax(int l, int r) {
        int k = std::__lg(r - l + 1);
        return std::max(f[l][k], f[r - (1ll << k) + 1][k]);
    }
    int askMin(int l, int r) {
        int k = std::__lg(r - l + 1);
        return std::min(g[l][k], g[r - (1ll << k) + 1][k]);
    }
    int askGcd(int l, int r) {
        int k = std::__lg(r - l + 1);
        return std::gcd(h[l][k], h[r - (1ll << k) + 1][k]);
    }
};