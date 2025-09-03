template<class Merge, typename T>
class SparseTable {
private:
    const int n;
    const int lg;
    Merge merge = Merge();
    std::vector<std::vector<T>> f;
public:
    SparseTable(const std::vector<T>& a) : n(a.size()), lg(std::__lg(n)), f(n) {
        for (int i = 0; i < n; i++) {
            f[i].resize(lg + 1);
            f[i][0] = a[i];
        }
        for (int j = 1; j <= lg; j++) {
            for (int i = 0; i + (1LL << j) - 1 < n; i++) {
                f[i][j] = merge(f[i][j - 1], f[i + (1LL << (j - 1))][j - 1]);
            }
        }
    }
    constexpr T ask(int l, int r) {
        if (l > r) {
            return T();
        }
        l = std::max(0, l);
        r = std::min(n, r);
        std::size_t k = std::__lg(r - l);
        return merge(f[l][k], f[r - (1LL << k)][k]);
    }
    constexpr T operator ()(int l, int r) {
        return ask(l, r);
    };
};

template<typename T>
class Max {
public:
    constexpr T operator() (T l, T r) {
        return std::max(l, r);
    };
};