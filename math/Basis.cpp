using u64 = unsigned long long;
template<int N>
struct Basis {
    std::array<u64, N> p{};

    Basis() {
        p.fill(0);
    }

    bool add(u64 x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (p[i] == 0) {
                    p[i] = x;
                    return true;
                }
                x ^= p[i];
            }
        }
        return false;
    }

    u64 query() {
        u64 ans = 0;
        for (int i = N - 1; i >= 0; i--) {
            if ((ans ^ p[i]) > ans) {
                ans ^= p[i];
            }
        }
        return ans;
    }

    bool find(u64 x) {
        for (int i = N - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (p[i] == 0) {
                    return true;
                }
                x ^= p[i];
            }
        }
        return false;
    }
};