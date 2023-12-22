#include <bits/stdc++.h>

using i64 = long long;

template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (int i = 0; i < v.size(); i++) os << v[i] << " "[i != v.size() - 1]; return os; }

constexpr int P = 1000000007;

i64 power(i64 a, i64 b, int P = ::P) {
    i64 res = 1;
    a %= P;
    for (; b; b /= 2, a = a * a % P) {
        if (b % 2) {
            res = res * a % P;
        }
    }
    return res;
}

struct Node {
    int l, r;
    mutable i64 v;
    Node(const int& l, const int& r = 0, const i64& v = 0) :l(l), r(r), v(v) {}
    bool operator<(const Node& t) const { return l < t.l; }
};

template <class Node>
struct ChthollyTree {
    std::set<Node> S;

    ChthollyTree(std::vector<int> w) {
        for (int i = 0; i < w.size(); i++) {
            S.emplace(i, i, w[i]);
        }
    }

    void insert(const Node& t) {
        S.emplace(t);
    }

    auto split(int pos) {
        auto it = S.lower_bound(Node(pos));
        if (it != S.end() && it->l == pos) {
            return it;
        }
        --it;
        int l = it->l, r = it->r;
        i64 v = it->v;
        S.erase(it);
        S.emplace(l, pos - 1, v);
        return S.emplace(pos, r, v).first;
    }

    void assign(int l, int r, int v) {
        auto it2 = split(r + 1), it1 = split(l);
        S.erase(it1, it2);
        S.emplace(l, r, v);
    }

    void rangeAdd(int l, int r, int v) {
        auto it2 = split(r + 1), it1 = split(l);
        for (auto it = it1; it != it2; ++it) {
            it->v += v;
        }
    }

    void rangeCover(int l, int r, int v) {
        auto it2 = split(r + 1), it1 = split(l);
        S.erase(it1, it2);
        S.emplace(l, r, v);
    }

    i64 rangeKth(int l, int r, int k) {
        auto it2 = split(r + 1), it1 = split(l);
        std::vector<std::pair<i64, int>> t;
        for (auto it = it1; it != it2; ++it) {
            t.emplace_back(it->v, it->r - it->l + 1);
        }
        std::ranges::sort(t);
        for (auto& [x, siz] : t) {
            k -= siz;
            if (k <= 0) {
                return x;
            }
        }
        return -1;
    }

    i64 rangeSum(int l, int r, int x, int y) {
        i64 ans = 0;
        auto it2 = split(r + 1), it1 = split(l);
        for (auto it = it1; it != it2; ++it) {
            ans = (ans + power(it->v, x, y) * (it->r - it->l + 1) % y) % y;
        }
        return ans;
    }
};

int32_t main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int n, m, seed, vmax;
    std::cin >> n >> m >> seed >> vmax;

    std::vector<int> a(n);

    auto rnd = [&]() {
        auto ret = seed;
        seed = (7LL * seed + 13) % P;
        return ret;
    };

    for (int& x : a) {
        x = rnd() % vmax + 1;
    }

    ChthollyTree<Node> odt(a);

    while (m--) {
        int op = rnd() % 4 + 1;
        int l = rnd() % n;
        int r = rnd() % n;

        if (l > r) std::swap(l, r);

        int x;
        if (op == 3) {
            x = rnd() % (r - l + 1) + 1;
        }
        else {
            x = rnd() % vmax + 1;
        }

        if (op == 1) {
            odt.rangeAdd(l, r, x);
        }
        else if (op == 2) {
            odt.rangeCover(l, r, x);
        }
        else if (op == 3) {
            std::cout << odt.rangeKth(l, r, x) << "\n";
        }
        else {
            int y = rnd() % vmax + 1;
            std::cout << odt.rangeSum(l, r, x, y) << "\n";
        }
    }

    return 0;
}