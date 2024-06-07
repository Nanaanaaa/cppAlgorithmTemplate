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
using i64 = long long;
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

constexpr i64 mul(i64 base, i64 exp, i64 mod) {
    i64 res = base * exp - i64(1.L * base * exp / mod) * mod;
    res %= mod;
    if (res < 0) {
        res += mod;
    }
    return res;
}

template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x{ 0 } {}
    constexpr MInt(i64 x) : x{ norm(x % getMod()) } {}

    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt& operator*=(MInt rhs)& {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt& operator+=(MInt rhs)& {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt& operator-=(MInt rhs)& {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt& operator/=(MInt rhs)& {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream& operator>>(std::istream& is, MInt& a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const MInt& a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};

template<>
i64 MInt<0>::Mod = 998244353;

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
const int P = findPrime(rnd() % 900000000 + 100000000);
const int B = rnd() % P;
using Z = MInt<P>;

struct StringHash {
    int n;
    std::vector<Z> h, p, r;
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
            p[i + 1] *= B;
            h[i + 1] = h[i + 1] * B + s[i];
            r[i + 1] = r[i + 1] * B + s[n - 1 - i];
        }
    }

    void add(char c) { // r is not available
        p.push_back(p.back() * B);
        h.push_back(h.back() * B + c);
    }

    constexpr int get(int l, int r) {
        return h[r] + (P - h[l]) * p[r - l];
    }
    constexpr bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    constexpr bool isPalindrom(int x, int y) {
        return r[n - x] + (P - r[n - y]) * p[y - x] == get(x, y);
    }
    constexpr int operator()(int l, int r) {
        return get(l, r);
    }
    constexpr bool operator()(int a, int b, int c, int d) {
        return same(a, b, c, d);
    }
};