#include <bits/stdc++.h>

template<typename P, typename Q> constexpr std::istream& operator>>(std::istream& is, std::pair<P, Q>& v) { std::cin >> v.first >> v.second; return is; }
template<typename P, typename Q> constexpr std::ostream& operator<<(std::ostream& os, std::pair<P, Q>& v) { std::cout << v.first << ' ' << v.second; return os; }
template<typename T, std::size_t N> constexpr std::istream& operator>>(std::istream& is, std::array<T, N>& v) { for (auto& i : v) is >> i; return is; }
template<typename T, std::size_t N> constexpr std::ostream& operator<<(std::ostream& os, std::array<T, N>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename T> constexpr std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> constexpr std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename...Args> constexpr void debug(Args...args) { ((std::cerr << args << ' '), ...); std::cerr << '\n'; }
template<typename...Args> constexpr void println(Args...args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }
template<typename P, typename Q> constexpr void chmax(P& a, Q b) { a = (b > a ? b : a); }
template<typename P, typename Q> constexpr void chmin(P& a, Q b) { a = (b < a ? b : a); }

using i64 = int64_t;

constexpr int N = 1e6;

template <typename T = int>
struct Fenwick {
    int n;
    std::vector<T> tr;

    Fenwick(int n = 0) {
        init(n);
    }

    Fenwick(const std::vector<T>& init_) {
        init(init_.size());
        for (int i = 0; i < n; i++) {
            add(i, init_[i]);
        }
    }

    void init(int n) {
        this->n = n;
        tr.assign(n, 0);
    }

    void add(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tr[x - 1] += v;
        }
    }

    T preQuery(int x) {
        T ans = T();
        for (; x; x -= x & -x) {
            ans += tr[x - 1];
        }
        return ans;
    }

    T rangeQuery(int l, int r) {
        return preQuery(r) - preQuery(l);
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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto& x : a) {
        std::cin >> x;
        x--;
    }

    std::vector<std::vector<std::array<int, 2>>> qry(n);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--, r--;
        qry[r].push_back({ l, i });
    }

    std::vector<int> ans(m);
    Fenwick fen(n);
    std::vector<int> lst(N, -1);

    for (int r = 0; r < n; r++) {
        if (lst[a[r]] != -1) {
            fen.add(lst[a[r]], -1);
        }
        fen.add(r, 1);
        lst[a[r]] = r;
        for (auto [l, i] : qry[r]) {
            ans[i] = fen.rangeQuery(l, r + 1);
        }
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}