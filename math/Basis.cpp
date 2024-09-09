template<int N>
struct Basis {
    std::array<i64, N> p{};

    Basis() {
        p.fill(-1);
    }

    bool add(i64 x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (p[i] == -1) {
                    p[i] = x;
                    return true;
                }
                x ^= p[i];
            }
        }
        return false;
    }

    i64 query() {
        i64 ans = 0;
        for (int i = N - 1; i >= 0; i--) {
            if ((ans ^ p[i]) > ans) {
                ans ^= p[i];
            }
        }
        return ans;
    }

    bool find(i64 x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (p[i] == -1) {
                    return true;
                }
                x ^= p[i];
            }
        }
        return false;
    }
};