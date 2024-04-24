template<class T, class Merge = std::plus<T>>
struct Block {
    constexpr static int M = 500;
    const int n;
    const Merge merge;

    std::vector<T> a;
    std::array<T, M> t;
    std::array<T, M> s;
    std::vector<int> bel;

    Block(int n, const T& v = T()) :Block(std::vector<T>(n, v)) {}

    Block(std::vector<T>& _init)
        :n(_init.size()), bel(n + 1), a(_init), merge(Merge()) {
        t.fill(T());
        s.fill(T());
        for (int i = 0; i <= n; i++) {
            bel[i] = i / M;
            s[bel[i]] += a[i];
        }
    }

    void add(int l, int r, const T& v) { // [l, r)
        for (; (!l || bel[l] == bel[l - 1]) && l < r; l++) {
            a[l] = merge(a[l], v);
            s[bel[l]] = merge(s[bel[l]], v);
        }
        for (; bel[r] == bel[r - 1] && l < r; r--) {
            a[r - 1] = merge(a[r - 1], v);
            s[bel[r - 1]] = merge(s[bel[r - 1]], v);
        }
        for (int i = bel[l]; i < bel[r]; i++) {
            t[i] = merge(t[i], v);
            s[i] = merge(s[i], v * M);
        }
    }

    void add(int x, const T& v) {
        add(x, x + 1, v);
    }

    constexpr T operator[](int i) {
        return merge(a[i], t[bel[i]]);
    }
    constexpr T operator()(int l, int r) {
        T res = T();
        for (; (!l || bel[l] == bel[l - 1]) && l < r; l++) {
            res = merge(res, a[l]);
            res = merge(res, t[bel[l]]);
        }
        for (; bel[r] == bel[r - 1] && l < r; r--) {
            res = merge(res, a[r - 1]);
            res = merge(res, t[bel[r - 1]]);
        }
        for (int i = bel[l]; i < bel[r]; i++) {
            res = merge(res, s[i]);
        }
        return res;
    }
};