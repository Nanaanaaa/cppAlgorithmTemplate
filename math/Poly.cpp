template<class T>
constexpr T power(T a, uint64_t e, T res = T(1)) {
    for (; e != 0; e >>= 1, a *= a) {
        if (e & 1) {
            res *= a;
        }
    }
    return res;
}

template<uint32_t P>
constexpr uint32_t mulMod(uint32_t a, uint32_t b) {
    return uint64_t(a) * b % P;
}

template<uint64_t P>
constexpr uint64_t mulMod(uint64_t a, uint64_t b) {
    uint64_t res = a * b - uint64_t(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<std::unsigned_integral U, U P>
class ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    template<std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_% mod()) {}
    template<std::signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = std::make_signed_t<U>;
        S v = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }
    constexpr static U mod() {
        return P;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        return power(*this, mod() - 2);
    }

    constexpr ModIntBase& operator*=(const ModIntBase& rhs)& {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase& operator+=(const ModIntBase& rhs)& {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr ModIntBase& operator-=(const ModIntBase& rhs)& {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr ModIntBase& operator/=(const ModIntBase& rhs)& {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream& operator>>(std::istream& is, ModIntBase& a) {
        int64_t i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const ModIntBase& a) {
        return os << a.val();
    }

    friend constexpr std::strong_ordering operator<=>(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() <=> rhs.val();
    }

    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }

    constexpr U operator()() const {
        return val();
    }

    constexpr ModIntBase& operator++() {
        *this += 1;
        return *this;
    }

    constexpr ModIntBase operator++(int) {
        ModIntBase temp = *this;
        ++*this;
        return temp;
    }

    constexpr ModIntBase& operator--() {
        *this -= 1;
        return *this;
    }

    constexpr ModIntBase operator--(int) {
        ModIntBase temp = *this;
        --*this;
        return temp;
    }

    constexpr ModIntBase pow(uint64_t e) const {
        return power(*this, e);
    }

    friend constexpr ModIntBase operator^(ModIntBase a, uint64_t e) {
        return power(a, e);
    }

    friend constexpr ModIntBase pow(ModIntBase a, uint64_t e) {
        return power(a, e);
    }
private:
    U x;
};

template<uint32_t P>
using ModInt = ModIntBase<uint32_t, P>;
template<uint64_t P>
using ModInt64 = ModIntBase<uint64_t, P>;

using modint1000000007 = ModInt<1000000007U>;
using modint998244353 = ModInt<998244353U>;

using mint = modint998244353;

inline constexpr mint operator""_Z(unsigned long long v) {
    return mint(v);
}
inline constexpr mint operator""_z(unsigned long long v) {
    return mint(v);
}

#ifdef __cpp_lib_format
template<std::unsigned_integral U, U P>
struct std::formatter<ModIntBase<U, P>> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const ModIntBase<U, P>& x, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{}", x());
    }
};
#endif


std::vector<int> rev;
template<uint32_t P>
std::vector<ModInt<P>> roots{ 0, 1 };

template<uint32_t P>
constexpr ModInt<P> findPrimitiveRoot() {
    ModInt<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2) != 1) {
            break;
        }
        i += 1;
    }
    return power(i, (P - 1) >> k);
}

template<uint32_t P>
constexpr ModInt<P> primitiveRoot = findPrimitiveRoot<P>();

template<>
constexpr ModInt<998244353> primitiveRoot<998244353> {31};

template<uint32_t P>
constexpr void dft(std::vector<ModInt<P>>& a) {
    int n = a.size();

    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }

    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (roots<P>.size() < n) {
        int k = __builtin_ctz(roots<P>.size());
        roots<P>.resize(n);
        while ((1 << k) < n) {
            auto e = power(primitiveRoot<P>, 1 << (__builtin_ctz(P - 1) - k - 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots<P>[2 * i] = roots<P>[i];
                roots<P>[2 * i + 1] = roots<P>[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ModInt<P> u = a[i + j];
                ModInt<P> v = a[i + j + k] * roots<P>[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

template<uint32_t P>
constexpr void idft(std::vector<ModInt<P>>& a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    ModInt<P> inv = ModInt<P>(n).inv();
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}

template<uint32_t P = 998244353>
struct Poly : public std::vector<ModInt<P>> {
    using Value = ModInt<P>;

    Poly() : std::vector<Value>() {}
    explicit constexpr Poly(int n) : std::vector<Value>(n) {}

    explicit constexpr Poly(const std::vector<Value>& a) : std::vector<Value>(a) {}
    constexpr Poly(const std::initializer_list<Value>& a) : std::vector<Value>(a) {}

    template<class InputIt> // removed std::_RequireInputIter constraint for standard C++ compatibility
    explicit constexpr Poly(InputIt first, InputIt last) : std::vector<Value>(first, last) {}

    template<class F>
    explicit constexpr Poly(int n, F f) : std::vector<Value>(n) {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }

    constexpr Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (int(this->size()) <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }
    constexpr Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    constexpr friend Poly operator+(const Poly& a, const Poly& b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(a.size()); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < int(b.size()); i++) {
            res[i] += b[i];
        }
        return res;
    }
    constexpr friend Poly operator-(const Poly& a, const Poly& b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(a.size()); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < int(b.size()); i++) {
            res[i] -= b[i];
        }
        return res;
    }
    constexpr friend Poly operator-(const Poly& a) {
        std::vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = -a[i];
        }
        return Poly(res);
    }
    constexpr friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        if (a.size() < b.size()) {
            std::swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < int(a.size()); i++) {
                for (int j = 0; j < int(b.size()); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        idft(a);
        a.resize(tot);
        return a;
    }
    constexpr friend Poly operator*(Value a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    constexpr friend Poly operator*(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    constexpr friend Poly operator/(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] /= b;
        }
        return a;
    }
    constexpr Poly& operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    constexpr Poly& operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    constexpr Poly& operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    constexpr Poly& operator*=(Value b) {
        return (*this) = (*this) * b;
    }
    constexpr Poly& operator/=(Value b) {
        return (*this) = (*this) / b;
    }
    constexpr Poly deriv() const {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < int(this->size()) - 1; ++i) {
            res[i] = Value(i + 1) * (*this)[i + 1];
        }
        return res;
    }
    constexpr Poly integr() const {
        Poly res(this->size() + 1);
        for (int i = 0; i < int(this->size()); ++i) {
            res[i + 1] = (*this)[i] / Value(i + 1);
        }
        return res;
    }
    constexpr Poly inv(int m) const {
        Poly x{ (*this)[0].inv() };
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{ 2 } - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }
    constexpr Poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }
    constexpr Poly exp(int m) const {
        Poly x{ 1 };
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{ 1 } - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }
    // constexpr Poly pow(int k, int m) const {
    //     int i = 0;
    //     while (i < int(this->size()) && (*this)[i] == 0) {
    //         i++;
    //     }
    //     if (i == int(this->size()) || 1LL * i * k >= m) {
    //         return Poly(m);
    //     }
    //     Value v = (*this)[i];
    //     auto f = shift(-i) * v.inv();
    //     return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    // }

    constexpr Poly pow(i64 k, int m) const {
        int i = 0;
        while (i < int(this->size()) && (*this)[i] == 0) {
            i++;
        }

        if (i == int(this->size()) || 1LL * i * k >= m) {
            return Poly(m);
        }

        Value v = (*this)[i];

        Poly f = shift(-i) * v.inv();
        std::vector<std::pair<int, Value>> nz;
        for (int j = 1; j < f.size(); j++) {
            if (f[j] != 0) {
                nz.emplace_back(j, f[j]);
            }
        }

        Poly g;
        std::size_t len = m - i * k;

        if (nz.size() <= (P == 998244353 ? 100 : 1300)) {
            g = Poly(len);
            if (len > 0) {
                g[0] = 1;
            }

            for (int n = 0; n + 1 < len; n++) {
                Value sum = 0;
                for (auto p : nz) {
                    int d = p.first;
                    if (d > n + 1) {
                        break;
                    }
                    sum += p.second * g[n - d + 1] * (Value(k) * d - (n - d + 1));
                }
                g[n + 1] = sum * Value(n + 1).inv();
            }
        } else {
            g = (f.log(len) * Value(k)).exp(len);
        }

        return (g.shift(i * k).trunc(m)) * power(v, k);
    }

    constexpr Poly sqrt(int m) const {
        Poly x{ 1 };
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * Value(2).inv();
        }
        return x.trunc(m);
    }
    constexpr Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    constexpr std::vector<Value> eval(std::vector<Value> x) const {
        if (this->size() == 0) {
            return std::vector<Value>(x.size(), 0);
        }
        const int n = std::max(int(x.size()), int(this->size()));
        std::vector<Poly> q(4 * n);
        std::vector<Value> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{ 1, -x[l] };
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

template<uint32_t P = 998244353>
Poly<P> berlekampMassey(const Poly<P>& s) {
    Poly<P> c;
    Poly<P> oldC;
    int f = -1;
    for (int i = 0; i < int(s.size()); i++) {
        auto delta = s[i];
        for (int j = 1; j <= int(c.size()); j++) {
            delta -= c[j - 1] * s[i - j];
        }
        if (delta == 0) {
            continue;
        }
        if (f == -1) {
            c.resize(i + 1);
            f = i;
        } else {
            auto d = oldC;
            d *= -1;
            d.insert(d.begin(), 1);
            ModInt<P> df1 = 0;
            for (int j = 1; j <= int(d.size()); j++) {
                df1 += d[j - 1] * s[f + 1 - j];
            }
            assert(df1 != 0);
            auto coef = delta / df1;
            d *= coef;
            Poly<P> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            auto temp = c;
            c += d;
            if (i - int(temp.size()) > f - int(oldC.size())) {
                oldC = temp;
                f = i;
            }
        }
    }
    c *= -1;
    c.insert(c.begin(), 1);
    return c;
}


template<uint32_t P = 998244353>
ModInt<P> linearRecurrence(Poly<P> p, Poly<P> q, int64_t n) {
    int m = q.size() - 1;
    while (n > 0) {
        auto newq = q;
        for (int i = 1; i <= m; i += 2) {
            newq[i] *= -1;
        }
        auto newp = p * newq;
        newq = q * newq;
        for (int i = 0; i < m; i++) {
            p[i] = newp[i * 2 + n % 2];
        }
        for (int i = 0; i <= m; i++) {
            q[i] = newq[i * 2];
        }
        n /= 2;
    }
    return p[0] / q[0];
}

// Global Combinatorics using the default mint
using Z = mint;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{ 0 }, _fac{ 1 }, _invfac{ 1 }, _inv{ 0 } {}
    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        m = std::min(m, (int)Z::mod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * Z(i);
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * Z(i);
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

// Assuming Poly<998244353> for the 'get' function as it uses 'comb' (which uses mint)
Poly<998244353> get(int n, int m) {
    if (m == 0) {
        return Poly<998244353>(n + 1);
    }
    if (m % 2 == 1) {
        auto f = get(n, m - 1);
        Z p = 1;
        for (int i = 0; i <= n; i++) {
            f[n - i] += comb.binom(n, i) * p;
            p *= m;
        }
        return f;
    }
    auto f = get(n, m / 2);
    auto fm = f;
    for (int i = 0; i <= n; i++) {
        fm[i] *= comb.fac(i);
    }
    Poly<998244353> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * Z(m / 2);
    }
    for (int i = 0; i <= n; i++) {
        pw[i] *= comb.invfac(i);
    }
    fm = fm.mulT(pw);
    for (int i = 0; i <= n; i++) {
        fm[i] *= comb.invfac(i);
    }
    return f + fm;
}