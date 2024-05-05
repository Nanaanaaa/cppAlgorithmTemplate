constexpr bool isprime(int n) {
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

constexpr int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

struct StringHash {
    const static int P, B;
    int n;
    std::vector<int> h, p, r;
    StringHash() {}
    constexpr StringHash(std::string_view s) {
        init(s);
    }
    constexpr void init(std::string_view s) {
        n = s.size();
        p.assign(n + 1, 1);
        h.assign(n + 1, 0);
        r.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            p[i + 1] = 1LL * B * p[i] % P;
            h[i + 1] = (1LL * B * h[i] + s[i]) % P;
            r[i + 1] = (1LL * B * r[i] + s[n - 1 - i]) % P;
        }
    }

    constexpr int get(int l, int r) {
        return (h[r] + 1LL * (P - h[l]) * p[r - l]) % P;
    }
    constexpr bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    constexpr bool isPalindrom(int x, int y) {
        return (r[n - x] + 1LL * (P - r[n - y]) * p[y - x]) % P == get(x, y);
    }
    constexpr int operator()(int l, int r) {
        return get(l, r);
    }
    constexpr bool operator()(int a, int b, int c, int d) {
        return same(a, b, c, d);
    }
};
std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
const int StringHash::P = findPrime(rnd() % 900000000 + 100000000);
const int StringHash::B = rnd() % P;