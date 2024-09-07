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

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
const int P = findPrime(rnd() % 900000000 + 100000000);
const int B = rnd() % P;

template<class T>
constexpr T power(T base, i64 exp) {
    T res{ 1 };
    for (; exp; exp /= 2, base *= base) {
        if (exp % 2) {
            res *= base;
        }
    }
    return res;
}

struct Z {
    i64 x;
    constexpr Z() : x{ 0 } {}
    constexpr Z(i64 x) : x{ norm(x % P) } {}

    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr Z operator-() const {
        Z res;
        res.x = norm(P - x);
        return res;
    }
    constexpr Z inv() const {
        return power(*this, P - 2);
    }
    constexpr Z& operator*=(Z rhs)& {
        x = x * rhs.x % P;
        return *this;
    }
    constexpr Z& operator+=(Z rhs)& {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Z& operator-=(Z rhs)& {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Z& operator/=(Z rhs)& {
        return *this *= rhs.inv();
    }
    friend constexpr Z operator*(Z lhs, Z rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Z operator+(Z lhs, Z rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Z operator-(Z lhs, Z rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Z operator/(Z lhs, Z rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator==(Z lhs, Z rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Z lhs, Z rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(Z lhs, Z rhs) {
        return lhs.val() < rhs.val();
    }
};
const Z invB = Z(B).inv();

namespace coef {
    int n;
    std::vector<Z> _p{ 1 }, _q{ 1 };
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
    Z q(int m);
    Z p(int m) {
        if (m < 0) {
            return q(-m);
        }
        if (m > n) {
            init(2 * m);
        }
        return _p[m];
    }
    Z q(int m) {
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
    Z x;
    int siz;
    Hash(Z x = 0, int siz = 0) : x(x), siz(siz) {}
    Z val() const {
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
    std::vector<Z> h, r;
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