constexpr int64_t mul(int64_t a, int64_t b, int64_t p) {
    int64_t res = a * b - int64_t(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<class T>
constexpr T power(T base, int64_t exp) {
    T res{ 1 };
    for (; exp; exp >>= 1, base *= base) {
        if (exp & 1) {
            res *= base;
        }
    }
    return res;
}

constexpr int64_t power(int64_t a, int64_t b, int64_t p) {
    int64_t res = 1 % p;
    for (; b; b >>= 1, a = mul(a, a, p)) {
        if (b & 1) {
            res = mul(res, a, p);
        }
    }
    return res;
}

bool isprime(int64_t n) {
    if (n < 2) {
        return false;
    }
    static constexpr int A[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    const int s = std::__countr_zero(n - 1);
    const int64_t d = (n - 1) >> s;

    for (auto&& a : A) {
        if (a == n) {
            return true;
        }
        int64_t x = power(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool ok = false;
        for (int i = 0; i < s - 1; i++) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}

int64_t findPrime(int64_t n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
constexpr int64_t __M = 1e18;
const int64_t P = findPrime(rnd() % __M + __M);
const int64_t B = findPrime(rnd() % P + __M);

template<int64_t P>
struct MLong {
    int64_t x;
    constexpr MLong() : x{} {}
    constexpr MLong(int64_t x) : x{ norm(x % getMod()) } {}

    static int64_t Mod;
    constexpr static int64_t getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int64_t Mod_) {
        Mod = Mod_;
    }
    constexpr int64_t norm(int64_t x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int64_t val() const {
        return x;
    }
    explicit constexpr operator int64_t() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong& operator*=(MLong rhs)& {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong& operator+=(MLong rhs)& {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong& operator-=(MLong rhs)& {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong& operator/=(MLong rhs)& {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream& operator>>(std::istream& is, MLong& a) {
        int64_t v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const MLong& a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int64_t MLong<0LL>::Mod = P;

using mlong = MLong<0LL>;
const mlong invB = mlong(B).inv();

namespace coef {
    int n;
    std::vector<mlong> _p{ 1 }, _q{ 1 };
    void init(int m) {
        if (m <= n) {
            return;
        }
        _p.resize(m + 1);
        _q.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _p[i] = _p[i - 1] * B;
            _q[i] = _q[i - 1] * invB;
        }
        n = m;
    }
    mlong q(int m);
    mlong p(int m) {
        if (m < 0) {
            return q(-m);
        }
        if (m > n) {
            init(2 * m);
        }
        return _p[m];
    }
    mlong q(int m) {
        if (m < 0) {
            return p(-m);
        }
        if (m > n) {
            init(2 * m);
        }
        return _q[m];
    }
};

struct Hash {
    mlong x;
    int siz;
    Hash(mlong x = 0, int siz = 0) : x(x), siz(siz) {}
    int64_t val() const {
        return x.val();
    }
    constexpr friend Hash operator+(const Hash& a, const Hash& b) {
        return Hash(a.val() + b.val() * coef::p(a.siz), a.siz + b.siz);
    }
    constexpr friend Hash operator-(const Hash& a, const Hash& b) {
        assert(a.siz >= b.siz);
        return Hash((a.val() - b.val()) * coef::q(b.siz), a.siz - b.siz);
    }
    constexpr friend bool operator==(const Hash& a, const Hash& b) {
        return a.val() == b.val();
    }
    constexpr friend bool operator!=(const Hash& a, const Hash& b) {
        return a.val() != b.val();
    }
};

struct StringHash { // a0 * b ^ 0 + a1 * b ^ 1 + ... + ai * B ^ i + ... + an * B ^ n;
    int n;
    std::vector<mlong> h, r;
    StringHash() { n = 0; h.push_back(0), r.push_back(0); }
    StringHash(const char* s) {
        init(std::string_view(s));
    }
    StringHash(std::string_view s) {
        init(s);
    }
    void init(std::string_view s) {
        n = s.size();
        h.assign(n + 1, 0);
        r.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            h[i + 1] = h[i] + coef::p(i) * s[i];
            r[i + 1] = r[i] + coef::p(i) * s[n - 1 - i];
        }
    }
    void add(char c) { // r is not available from now
        h.push_back(h.back() + coef::p(n++) * c);
    }
    Hash get(int l, int r) {
        return Hash((h[r] - h[l]) * coef::q(l), r - l);
    }
    bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    bool isPalindrom(int x, int y) { // only available when not add
        return (r[n - x] - r[n - y]) * coef::q(n - y) == get(x, y).val();
    }
    constexpr Hash operator()(int l, int r) {
        return get(l, r);
    }
    constexpr bool operator()(int a, int b, int c, int d) {
        return same(a, b, c, d);
    }
};