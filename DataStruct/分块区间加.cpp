using i64 = int64_t;

constexpr int M = 750, N = 5e5 + 1;

i64 a[N];
i64 sum[M], tag[M];

constexpr int bel(int i) {
    return i / M;
}

constexpr void modify(int l, int r, int v) {
    if (bel(l) == bel(r)) {
        for (int i = l; i <= r; i++) {
            a[i] += v;
            sum[bel(i)] += v;
        }
    }
    else {
        int i = l, j = r;
        for (; bel(i) == bel(l); i++) {
            a[i] += v;
            sum[bel(i)] += v;
        }
        for (; bel(j) == bel(r); j--) {
            a[j] += v;
            sum[bel(j)] += v;
        }
        for (int k = bel(i); k <= bel(j); k++) {
            sum[k] += 1LL * M * v;
            tag[k] += v;
        }
    }
}

constexpr i64 query(int l, int r) {
    i64 ans = 0;
    if (bel(l) == bel(r)) {
        for (int i = l; i <= r; i++) {
            ans += a[i] + tag[bel(i)];
        }
    }
    else {
        int i = l, j = r;
        for (; bel(i) == bel(l); i++) {
            ans += a[i] + tag[bel(i)];
        }
        for (; bel(j) == bel(r); j--) {
            ans += a[j] + tag[bel(j)];
        }
        for (int k = bel(i); k <= bel(j); k++) {
            ans += sum[k];
        }
    }
    return ans;
}