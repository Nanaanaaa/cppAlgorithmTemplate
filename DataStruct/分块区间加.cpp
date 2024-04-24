#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int M = 500;

template<class T = int>
struct Block {
    int n;
    std::vector<T> a;
    std::vector<int> bel;
    std::array<i64, M> sum;
    std::array<i64, M> tag;
    constexpr Block(int n) :n(n), a(n), bel(n), sum{}, tag{} {
        for (int i = 0; i < n; i++) {
            bel[i] = i / M;
        }
    }
    constexpr Block(std::vector<T> init_) {
        Block(init_.size());
        for (int i = 0; i < n; i++) {
            a[i] = init_[i];
            sum[bel[i]] += init_[i];
        }
    }
    constexpr void add(int l, int r, const T& v) {
        r--;
        if (bel[l] == bel[r]) {
            for (int i = l; i <= r; i++) {
                a[i] += v;
                sum[bel[i]] += v;
            }
        } else {
            int i = l, j = r;
            for (; bel[i] == bel[l]; i++) {
                a[i] += v;
                sum[bel[i]] += v;
            }
            for (; bel[j] == bel[r]; j--) {
                a[j] += v;
                sum[bel[j]] += v;
            }
            for (int k = bel[i]; k <= bel[j]; k++) {
                sum[k] += 1LL * M * v;
                tag[k] += v;
            }
        }
    }
    constexpr void add(int x, const T& v) {
        return add(x, x + 1, v);
    }
    constexpr i64 query(int l, int r) {
        r--;
        i64 ans = 0;
        if (bel[l] == bel[r]) {
            for (int i = l; i <= r; i++) {
                ans += a[i] + tag[bel[i]];
            }
        } else {
            int i = l, j = r;
            for (; bel[i] == bel[l]; i++) {
                ans += a[i] + tag[bel[i]];
            }
            for (; bel[j] == bel[r]; j--) {
                ans += a[j] + tag[bel[j]];
            }
            for (int k = bel[i]; k <= bel[j]; k++) {
                ans += sum[k];
            }
        }
        return ans;
    }
    constexpr int operator[](int x) {
        return query(x, x + 1);
    }
    constexpr int operator()(int l, int r) {
        return query(l, r);
    }
};