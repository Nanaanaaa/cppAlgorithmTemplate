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

using mint64 = ModInt64<i64(1E18) + 9>;

inline constexpr mint64 operator "" _Z(unsigned long long v) {
    return mint64(v);
}
inline constexpr mint64 operator "" _z(unsigned long long v) {
    return mint64(v);
}

#if __cplusplus > 202002L
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

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
const mint64 Base = rnd();
const mint64 iBase = Base.inv();

namespace coef {
    int n;
    std::vector<mint64> _p{ 1 }, _ip{ 1 };
    void init(int m) {
        if (m <= n) {
            return;
        }
        _p.resize(m + 1);
        _ip.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _p[i] = _p[i - 1] * Base;
            _ip[i] = _ip[i - 1] * iBase;
        }
        n = m;
    }
    mint64 pw(int m);
    mint64 ipw(int m);
    mint64 pw(int m) {
        if (m < 0) {
            return ipw(-m);
        }
        if (m > n) {
            init(2 * m);
        }
        return _p[m];
    }
    mint64 ipw(int m) {
        if (m < 0) {
            return pw(-m);
        }
        if (m > n) {
            init(2 * m);
        }
        return _ip[m];
    }
};

class Hash {
public:
    Hash(mint64 x = 0, std::size_t siz = 0) : x(x), siz(siz) {}
    constexpr uint64_t val() const {
        return x.val();
    }
    constexpr uint64_t operator()() const {
        return x.val();
    }
    constexpr std::size_t size() const {
        return siz;
    }
    constexpr friend Hash operator+(const Hash& a, const Hash& b) {
        return Hash(a.val() + b.val() * coef::p(a.siz), a.siz + b.siz);
    }
    constexpr friend Hash operator-(const Hash& a, const Hash& b) {
        assert(a.siz >= b.siz);
        return Hash((a.val() - b.val()) * coef::ip(b.siz), a.siz - b.siz);
    }
    constexpr friend bool operator==(const Hash& a, const Hash& b) {
        return a.val() == b.val();
    }
    constexpr friend bool operator!=(const Hash& a, const Hash& b) {
        return a.val() != b.val();
    }

private:
    mint64 x;
    std::size_t siz;
};

struct StringHash { // a0 * b ^ 0 + a1 * b ^ 1 + ... + ai * B ^ i + ... + an * B ^ n;
    int n;
    std::vector<mint64> h, r;
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
        return Hash((h[r] - h[l]) * coef::ip(l), r - l);
    }
    bool same(int x, int y, int l, int r) {
        return get(x, y) == get(l, r);
    }
    bool isPalindrom(int x, int y) { // only available when not add
        return (r[n - x] - r[n - y]) * coef::ip(n - y) == get(x, y).val();
    }
    constexpr Hash operator()(int l, int r) {
        return get(l, r);
    }
    constexpr bool operator()(int a, int b, int c, int d) {
        return same(a, b, c, d);
    }
};