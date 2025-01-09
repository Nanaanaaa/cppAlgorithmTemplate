#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = long long;

template<typename T = int>
class Fenwick {
private:
    int n;
    std::vector<T> tr;
    struct Proxy {
        Fenwick& fen{};
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
        for (int i = 1 << std::__lg(n); i; i >>= 1) {
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

struct Query {
    int l, r, k, id, type;
};

constexpr int V = 1e9 + 1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<Query> query(n + q);

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        query[i] = { a[i], 1, 0, i, 1 };
    }

    for (int i = 0; i < q; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        query[i + n] = { l - 1, r, k, i, 2 };
    }

    std::vector<int> ans(q);
    Fenwick fen(n);

    auto work = [&](auto&& work, int l, int r, int x, int y) {
        if (x >= y) {
            return;
        }

        if (r - l == 1) {
            for (int i = x; i < y; i++) {
                if (query[i].type == 2) {
                    ans[query[i].id] = l;
                }
            }
            return;
        }

        int m = (l + r) / 2;
        std::vector<Query> ql, qr;

        for (int i = x; i < y; i++) {
            if (query[i].type == 1) {
                if (query[i].l < m) {
                    ql.push_back(query[i]);
                    fen[query[i].id]++;
                } else {
                    qr.push_back(query[i]);
                }
            } else {
                int s = fen(query[i].l, query[i].r);
                if (query[i].k <= s) {
                    ql.push_back(query[i]);
                } else {
                    query[i].k -= s;
                    qr.push_back(query[i]);
                }
            }
        }

        for (auto q : ql) {
            if (q.type == 1) {
                fen[q.id]--;
            }
        }

        stdr::copy(ql, query.begin() + x);
        stdr::copy(qr, query.begin() + x + ql.size());

        work(work, l, m, x, x + ql.size());
        work(work, m, r, x + ql.size(), y);
    };
    work(work, 0, V, 0, n + q);

    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}