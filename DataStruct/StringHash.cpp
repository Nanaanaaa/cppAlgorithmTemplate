std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct StringHash {
    const int P = findPrime(rnd() % 900000000 + 100000000);
    int n;
    std::vector<int> h, p, r;
    StringHash() {}
    StringHash(std::string_view s) {
        init(s);
    }
    void init(std::string_view s) {
        n = s.size();
        p.assign(n + 1, 1);
        h.assign(n + 1, 0);
        r.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            p[i + 1] = 10LL * p[i] % P;
            h[i + 1] = (10LL * h[i] + s[i]) % P;
            r[i + 1] = (10LL * r[i] + s[n - 1 - i]) % P;
        }
    }

    bool isprime(int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    int findPrime(int n) {
        while (!isprime(n)) {
            n++;
        }
        return n;
    }

    int get(int l, int r) { // 0开头 左闭右开
        return (h[r] + 1LL * (P - h[l]) * p[r - l]) % P;
    }
    bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    bool isPalindrom(int x, int y) {
        return (r[n - x] + 1LL * (P - r[n - y]) * p[y - x]) % P == get(x, y);
    }
};