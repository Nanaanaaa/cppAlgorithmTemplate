#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5, V = 1e9;
namespace T {
    int idx;
    struct Node {
        int l, r;
        int cnt;
    }tr[35 * N];

    int add(int p, int l, int r, int x, int v) {
        int q = p;
        if (!p) {
            q = ++idx;
        }
        tr[q] = tr[p];
        tr[q].cnt += v;
        if (r - l == 1) {
            return q;
        }
        int m = (l + r) / 2;
        if (x < m) {
            tr[q].l = add(tr[q].l, l, m, x, v);
        }
        else {
            tr[q].r = add(tr[q].r, m, r, x, v);
        }
        return q;
    }
    int add(int p, int x, int v) {
        return add(p, -V, V + 1, x, v);
    }
};
using namespace T;