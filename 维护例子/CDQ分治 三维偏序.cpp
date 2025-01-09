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

struct Info {
    int a, b, c;
    int cnt;
    int ans;

    constexpr friend bool operator<(const Info& l, const Info& r) {
        if (l.b == r.b) {
            return l.c < r.c;
        }
        return l.b < r.b;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, V;
    std::cin >> n >> V;

    std::vector<std::array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    std::sort(a.begin(), a.end());

    std::vector<Info> info;
    for (int i = 0; i < n; i++) {
        if (!info.empty() && std::array<int, 3>{info.back().a, info.back().b, info.back().c} == a[i]) {
            info.back().cnt++;
        } else {
            info.emplace_back(a[i][0], a[i][1], a[i][2], 1, 0);
        }
    }

    const int siz = info.size();
    Fenwick fen(1 + V);

    auto work = [&](auto&& work, int l, int r) {
        if (r - l == 1) {
            return;
        }

        int m = (l + r) / 2;
        work(work, l, m);
        work(work, m, r);

        std::sort(info.begin() + l, info.begin() + m);
        std::sort(info.begin() + m, info.begin() + r);

        int i = l;
        for (int j = m; j < r; j++) {
            for (; i < m && info[i].b <= info[j].b; i++) {
                fen[info[i].c] += info[i].cnt;
            }
            info[j].ans += fen.sum(info[j].c + 1);
        }
        for (int k = l; k < i; k++) {
            fen[info[k].c] -= info[k].cnt;
        }
    };
    work(work, 0, siz);

    std::vector<int> ans(n);
    for (auto t : info) {
        ans[t.ans + t.cnt - 1] += t.cnt;
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}