#include <bits/stdc++.h>

using i64 = int64_t;

struct Fenwick;

struct Info {
    int x, y, z;
    int cnt, res;

    constexpr bool operator!=(const Info& t) {
        if (x != t.x) return true;
        if (y != t.y) return true;
        if (z != t.z) return true;
        return false;
    }
};

constexpr bool cmp1(const Info& a, const Info& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

constexpr bool cmp2(const Info& a, const Info& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::vector<Info> a(n), b;
    for (auto& [x, y, z, cnt, res] : a) {
        std::cin >> x >> y >> z;
    }
    std::sort(a.begin(), a.end(), cmp1);

    for (int i = 0, t = 0; i < n; i++) {
        t++;
        if ((i + 1 < n && a[i] != a[i + 1]) || i == n - 1) {
            b.emplace_back(a[i]);
            b.back().cnt = t;
            t = 0;
        }
    }

    Fenwick fen(2E5 + 1);

    auto solve = [&](auto self, int l, int r) {
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        self(self, l, m);
        self(self, m, r);
        std::sort(b.begin() + l, b.begin() + m, cmp2);
        std::sort(b.begin() + m, b.begin() + r, cmp2);
        int i = l, j = m;
        for (; j < r; j++) {
            for (; i < m && b[i].y <= b[j].y; i++) {
                fen.add(b[i].z, b[i].cnt);
            }
            b[j].res += fen.preQuery(b[j].z + 1);
        }
        for (; l < i; l++) {
            fen.add(b[l].z, -b[l].cnt);
        }
    };

    const int m = b.size();

    solve(solve, 0, m);
    std::vector<int> ans(n);

    for (int i = 0; i < m; i++) {
        ans[b[i].res + b[i].cnt - 1] += b[i].cnt;
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}