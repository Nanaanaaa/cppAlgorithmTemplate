using u64 = uint64_t;
constexpr int B = 63;
struct LinearBasis {
    u64 p[B + 1]{};
    std::vector<u64> d;
    bool z = false;
    int r = 0;

    void add(u64 x) {
        for (int i = B; ~i; i--) {
            if (~x >> i & 1) {
                continue;
            }
            if (p[i] == 0) {
                p[i] = x;
                r++;
                return;
            }
            x ^= p[i];
        }
        z = true;
    }

    bool has(u64 x) {
        for (int i = B; ~i; i--) {
            if (x >> i & 1) {
                x ^= p[i];
            }
        }
        return x == 0;
    }

    u64 max() {
        u64 res = 0;
        for (int i = B; ~i; i--) {
            res = std::max(res, res ^ p[i]);
        }
        return res;
    }

    u64 min() {
        if (z) return 0;
        for (int i = 0; i <= B; i++) {
            if (p[i]) {
                return p[i];
            }
        }
        return 0;
    }

    void rebuild() {
        d.clear();
        for (int i = 0; i <= B; i++) {
            for (int j = i - 1; ~j; j--) {
                if (p[i] >> j & 1) {
                    p[i] ^= p[j];
                }
            }
            if (p[i]) {
                d.push_back(p[i]);
            }
        }
    }

    i64 kth(u64 k) {
        k -= z;
        if (k == 0) {
            return 0;
        }
        rebuild();
        if (k >= 1LL << d.size()) {
            return -1;
        }
        u64 res = 0;
        for (int i = B; ~i; i--) {
            if (k >> i & 1) {
                res ^= d[i];
            }
        }
        return res;
    }

    u64 rank(u64 x) {
        u64 r = 0;
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (x >= d[i]) {
                r += (1LL << i);
                x ^= d[i];
            }
        }
        return r + z;
    }
};