#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5, M = 500;

constexpr int bel(int i) {
    return i / M;
}

void modify(int l, int r) {
    if (bel(l) == bel(r)) {
        for (int i = l; i <= r; i++) {

        }
    }
    else {
        int i = l, j = r;
        for (; bel(i) == bel(l); i++) {

        }
        for (; bel(j) == bel(r); j--) {

            for (int k = bel(i); k <= bel(j); k++) {

            }
        }
    }
}

i64 query(int l, int r) {
    i64 ans = 0;
    if (bel(l) == bel(r)) {

    }
    else {
        int i = l, j = r;
        for (; bel(i) == bel(l); i++) {

        }
        for (; bel(j) == bel(r); j--) {

        }
        for (int k = bel(i); k <= bel(j); k++) {

        }
    }
    return ans;
}

int main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::vector<i64> sum(M), add(M);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        sum[bel(i)] += a[i];
    }

    return 0;
}