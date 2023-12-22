constexpr double eps = 1e-9;
template <class L>
struct LichaoTree {
    std::vector<L> f;
    std::vector<int> tr;
    std::pair<double, int> max(const std::pair<double, int>& a, const std::pair<double, int>& b) {
        auto [a1, a2] = a, auto [b1, b2] = b;
        if (a1 - b1 > eps) {
            return a;
        }
        else if (b1 - a1 > eps) {
            return b;
        }
        return a2 < b2 ? a : b;
    }

    void rangeApply(int p, int l, int r, int x, int y, int v) {
        int m = (l + r) / 2;
        if (l <= x && r <= y) {
            if (tr[p] == 0) {
                tr[p] = v;
                return;
            }
            int m = (l + r - 1) / 2;
            if (f[i][m])
        }
    }
};
struct Line {
    const int inf = 1e9;
    double k, b;
    int min, max;
    double operator()(int x) {
        if (min <= x && x <= max) return k * x + b;
        return -inf;
    }
};