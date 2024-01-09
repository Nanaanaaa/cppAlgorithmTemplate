template<class T = int, int M = 500>
struct Block {
    int n;
    std::vector<T> a;
    std::vector<i64> sum;
    std::vector<i64> tag;
    std::vector<int> bel;
    Block(int n) :n(n), a(n), sum(M), tag(M), bel(n) {
        for (int i = 0; i < n; i++) {
            bel[i] = i / M;
        }
    }
    Block(std::vector<T> init_) {
        Block(init_.size());
        for (int i = 0; i < n; i++) {
            a[i] = init_[i];
            sum[bel[i]] += init_[i];
        }
    }
    void modify(int l, int r, T v) {
        if (bel(l) == bel(r)) {
            for (int i = l; i <= r; i++) {
                a[i] += v;
                sum[bel[i]] += v;
            }
        }
        else {
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
    void modify(int x, T v) {
        return modify(x, x, v);
    }
    i64 query(int l, int r) {
        i64 ans = 0;
        if (bel[l] == bel[r]) {
            for (int i = l; i <= r; i++) {
                ans += a[i] + tag[bel[i]];
            }
        }
        else {
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
    i64 query(int x) {
        return query(x, x);
    }
};