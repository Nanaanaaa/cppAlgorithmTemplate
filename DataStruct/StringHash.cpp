std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct StringHash {
    constexpr static int P1 = 998244351, P2 = 998244353;
    int B1 = 131, B2 = 13331;
    int n;
    std::vector<int> h1, h2, p1, p2;
    StringHash() {}
    StringHash(const std::string& s) {
        init(s);
    }
    void init(const std::string& s) {
        n = s.size();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        B1 = rnd() % 200 + 100;
        B2 = rnd() % 20000 + 10000;
        for (int i = 0; i < n; i++) {
            p1[i + 1] = 1LL * p1[i] * B1 % P1;
            p2[i + 1] = 1LL * p2[i] * B2 % P2;
            h1[i + 1] = (1LL * h1[i] * B1 + s[i]) % P1;
            h2[i + 1] = (1LL * h2[i] * B2 + s[i]) % P2;
        }
    }
    int get1(int l, int r) { // 0开头 左闭右开
        int res = (h1[r] - 1LL * h1[l] * p1[r - l] % P1) % P1;
        if (res < 0) res += P1;
        return res;
    }
    int get2(int l, int r) {
        int res = (h2[r] - 1LL * h2[l] * p2[r - l] % P2) % P2;
        if (res < 0) res += P2;
        return res;
    }
    bool same(int x, int y, int l, int r) {
        return get1(x, y) == get1(l, r) && get2(x, y) == get2(l, r);
    }
};