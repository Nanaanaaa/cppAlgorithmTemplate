template<typename T = int>
class Fenwick {
private:
    int n;
    std::vector<T> tr;
public:
    Fenwick(int n = 0) {
        init(n);
    }
    Fenwick(const std::vector<T>& init_) {
        init(init_.size());
        for (int i = 0; i < n; i++) {
            add(i, init_[i]);
        }
    }
    void init(int __n) {
        n = __n;
        tr.assign(n, {});
    }
    void add(int x, T v) {
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
    constexpr void operator+=(std::pair<int, T> t) {
        add(t.first, t.second);
    }
    constexpr T operator() (int x) {
        return sum(x);
    }
    constexpr T operator() (int l, int r) {
        return rangeSum(l, r);
    }
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= tr[x + i - 1]) {
                x += i;
                k -= tr[x - 1];
            }
        }
        return x;
    }
};