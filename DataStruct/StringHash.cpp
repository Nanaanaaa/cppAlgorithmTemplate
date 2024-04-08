std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct StringHash {
    constexpr static int P1 = 998244351, P2 = 998244353;
    int B1 = 131, B2 = 13331;
    int n;
    std::vector<int> h1, h2, p1, p2, r1, r2;
    StringHash() {}
    StringHash(std::string_view s) {
        init(s);
    }
    void init(std::string_view s) {
        n = s.size();
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        r1.assign(n + 1, 0);
        r2.assign(n + 1, 0);
        B1 = rnd() % 200 + 100;
        B2 = rnd() % 20000 + 10000;
        for (int i = 0; i < n; i++) {
            p1[i + 1] = 1LL * p1[i] * B1 % P1;
            p2[i + 1] = 1LL * p2[i] * B2 % P2;
            h1[i + 1] = (1LL * h1[i] * B1 + s[i]) % P1;
            h2[i + 1] = (1LL * h2[i] * B2 + s[i]) % P2;
            r1[i + 1] = (1LL * r1[i] * B1 + s[n - 1 - i]) % P1;
            r2[i + 1] = (1LL * r2[i] * B2 + s[n - 1 - i]) % P2;
        }
    }
    std::pair<int, int> get(int l, int r) { // 0开头 左闭右开
        int res1 = (h1[r] - 1LL * h1[l] * p1[r - l] % P1) % P1;
        if (res1 < 0) res1 += P1;
        int res2 = (h2[r] - 1LL * h2[l] * p2[r - l] % P2) % P2;
        if (res2 < 0) res2 += P2;
        return { res1, res2 };
    }

    bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    bool isPalindrom(int l, int r) {
        auto t = get(l, r);
        std::tie(l, r) = std::pair(n - r, n - l);
        int res1 = (r1[r] - 1LL * r1[l] * p1[r - l] % P1) % P1;
        if (res1 < 0) res1 += P1;
        int res2 = (r2[r] - 1LL * r2[l] * p2[r - l] % P2) % P2;
        if (res2 < 0) res2 += P2;
        return std::pair(res1, res2) == t;
    }
};
