#include <bits/stdc++.h>

using i64 = long long;

namespace S {
    constexpr int N = 1e5;

    int n;
    int init_[N];

    struct Info {
        int x;
        Info(int x = 0) :x(x) {}
    }tr[4 << std::__lg(N)];

    Info operator+(const Info& a, const Info& b) {
        return a.x + b.x;
    };

    void pull(int p) {
        tr[p] = tr[2 * p] + tr[2 * p + 1];
    }

#define m (l + r) / 2

    void build(int p, int l, int r) {
        if (r - l == 1) {
            tr[p] = init_[l];
            return;
        }
        build(2 * p, l, m);
        build(2 * p + 1, m, r);
        pull(p);
    }

    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            tr[p] = v;
            return;
        }
        if (x < m) {
            modify(2 * p, l, m, x, v);
        }
        else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, int x, const Info& v) {
        modify(1, 0, n, x, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return tr[p];
        }
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int p, int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

#undef m
}
using namespace S;