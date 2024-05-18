template<class Merge>
struct SparseTable {
    const int n;
    const int lg;
    Merge merge = Merge();
    std::vector<std::vector<int>> f;
    SparseTable(const std::vector<int>& a) :n(a.size()), lg(std::__lg(n)), f(n) {
        for (int i = 0; i < n; i++) {
            f[i].resize(lg + 1);
            f[i][0] = a[i];
        }
        for (int j = 1; (1LL << j) < n; j++) {
            for (int i = 0; i + (1LL << j) - 1 < n; i++) {
                f[i][j] = merge(f[i][j - 1], f[i + (1LL << (j - 1))][j - 1]);
            }
        }
    }
    constexpr int ask(int l, int r) {
        int k = std::__lg(r - l + 1);
        return merge(f[l][k], f[r - (1ll << k) + 1][k]);
    }
    constexpr int operator ()(int l, int r) { // [0, r)
        return ask(l, r - 1);
    };
};
