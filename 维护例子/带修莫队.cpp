#include <bits/stdc++.h>

template<typename P, typename Q> std::istream& operator>>(std::istream& is, std::pair<P, Q>& v) { std::cin >> v.first >> v.second; return is; }
template<typename P, typename Q> std::ostream& operator<<(std::ostream& os, std::pair<P, Q>& v) { std::cout << v.first << ' ' << v.second; return os; }
template<typename T, std::size_t N> std::istream& operator>>(std::istream& is, std::array<T, N>& v) { for (auto& i : v) is >> i; return is; }
template<typename T, std::size_t N> std::ostream& operator<<(std::ostream& os, std::array<T, N>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename...Args> void debug(Args...args) { ((std::cerr << args << ' '), ...); std::cerr << '\n'; }
template<typename...Args> void println(Args...args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }
template<typename P, typename Q> void chmax(P& a, Q b) { a = (b > a ? b : a); }
template<typename P, typename Q> void chmin(P& a, Q b) { a = (b < a ? b : a); }

using i64 = int64_t;

constexpr int N = 1e6 + 10, B = 4500; // 带修莫队的块长可以开大点 N = 1e5, M = 3050 开小了容易T

int cnt[N];

struct Info {
    int l = 0, r = 0, t = 0, i = 0;
    friend constexpr bool operator<(const Info& a, const Info& b) {
        if (a.l / B != b.l / B) {
            return a.l / B < b.l / B;
        }
        if (a.r / B != b.r / B) {
            return a.r / B < b.r / B;
        }
        return a.t < b.t;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> col(n);
    std::cin >> col;

    std::vector<Info> qry;
    std::vector<std::pair<int, int>> mdf;

    while (m--) {
        char o;
        std::cin >> o;
        if (o == 'Q') {
            int l, r;
            std::cin >> l >> r;
            l--, r--;
            qry.emplace_back(l, r, (int)mdf.size(), (int)qry.size());
        }
        else {
            int x, c;
            std::cin >> x >> c;
            x--;
            mdf.emplace_back(x, c);
        }
    }

    std::sort(qry.begin(), qry.end());

    int l = 1, r = 0, cur = 0, res = 0;

    auto add = [&](int i) {
        if (++cnt[col[i]] == 1) {
            res++;
        }
    };

    auto del = [&](int i) {
        if (--cnt[col[i]] == 0) {
            res--;
        }
    };

    auto modify = [&](int x, int y, int i) {
        auto& [p, c] = mdf[i];
        if (p >= x && p <= y) {
            if (--cnt[col[p]] == 0) {
                res--;
            }
            if (++cnt[c] == 1) {
                res++;
            }
        }
        std::swap(col[p], c);
    };

    std::vector<int> ans(qry.size());
    for (auto [x, y, t, i] : qry) {
        while (l < x) del(l++);
        while (l > x) add(--l);
        while (r < y) add(++r);
        while (r > y) del(r--);
        while (cur < t) modify(x, y, cur++);
        while (cur > t) modify(x, y, --cur);
        ans[i] = res;
    }

    for (const auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}