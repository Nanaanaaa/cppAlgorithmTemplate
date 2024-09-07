int lg(unsigned int x) {
    return std::bit_width(x) - 1;
}

template<typename T = int>
class Fenwick {
private:
    int n;
    std::vector<T> tr;
    struct Proxy {
        Fenwick<T>& fen{};
        int idx{};
        constexpr Proxy& operator+=(const T& v) {
            fen.add(idx, v);
            return *this;
        }
        constexpr Proxy& operator-=(const T& v) {
            fen.add(idx, -v);
            return *this;
        }
        constexpr Proxy& operator++() {
            fen.add(idx, 1);
            return *this;
        }
        constexpr Proxy& operator++(int) {
            fen.add(idx, 1);
            return *this;
        }
        constexpr Proxy& operator--() {
            fen.add(idx, -1);
            return *this;
        }
        constexpr Proxy& operator--(int) {
            fen.add(idx, -1);
            return *this;
        }
    };
public:
    explicit Fenwick(int n = 0, const T& init_ = T()) {
        init(n);
        for (int i = 0; i < n; i++) {
            add(i, init_);
        }
    }
    explicit Fenwick(const std::vector<T>& init_) {
        init(init_);
    }
    void init(int n_) {
        n = n_;
        tr.assign(n, {});
    }
    void init(const std::vector<T>& init_) {
        init(init_.size());
        for (int i = 0; i < n; i++) {
            add(i, init_[i]);
        }
    }
    void add(int x, const T& v) {
        for (++x; x <= n; x += x & -x) {
            tr[x - 1] += v;
        }
    }
    T sum(int x) {
        T ans = T();
        for (; x; x -= x & -x) {
            ans += tr[x - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int find(const T& k) {
        int x = 0;
        T cur{};
        for (int i = 1 << lg(n); i; i /= 2) {
            if (x + i <= n && cur + tr[x + i - 1] <= k) {
                x += i;
                cur = cur + tr[x - 1];
            }
        }
        return x;
    }
    constexpr Proxy operator[](int i) {
        return Proxy{ *this, i };
    }
    constexpr T operator() (int r) {
        return sum(r);
    }
    constexpr T operator() (int l, int r) {
        return rangeSum(l, r);
    }
};