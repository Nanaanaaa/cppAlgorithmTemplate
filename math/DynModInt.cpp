template<class T>
constexpr T power(T a, uint64_t b, T res = 1) {
    for (; b != 0; b >>= 1, a *= a) {
        if (b & 1) {
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

constexpr int64_t safeMod(int64_t x, int64_t m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr std::pair<int64_t, int64_t> invGcd(int64_t a, int64_t b) {
    a = safeMod(a, b);
    if (a == 0) {
        return { b, 0 };
    }

    int64_t s = b, t = a;
    int64_t m0 = 0, m1 = 1;

    while (t) {
        int64_t u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return { s, m0 };
}

template<std::unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    template<std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_% mod()) {}
    template<std::signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = std::make_signed_t<T>;
        S v = x_;
        v %= S(mod());
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

    constexpr U operator()() const {
        return val();
    }

    struct Formatter {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        template <typename FormatContext>
        auto format(const ModIntBase& x, FormatContext& ctx) const {
            return std::format_to(ctx.out(), "{}", x());
        }
    };

private:
    U x;
};

template<std::unsigned_integral U, U P>
struct std::formatter<ModIntBase<U, P>> : ModIntBase<U, P>::Formatter {};

template<uint32_t P>
using ModInt = ModIntBase<uint32_t, P>;
template<uint64_t P>
using ModInt64 = ModIntBase<uint64_t, P>;

using modint1000000007 = ModInt<1000000007>;
using modint998244353 = ModInt<998244353>;

struct Barrett {
public:
    Barrett(uint32_t m_) : m(m_), im((uint64_t)(-1) / m_ + 1) {}

    constexpr uint32_t mod() const {
        return m;
    }

    constexpr uint32_t mul(uint32_t a, uint32_t b) const {
        uint64_t z = a;
        z *= b;

        uint64_t x = uint64_t((__uint128_t(z) * im) >> 64);

        uint32_t v = uint32_t(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    uint32_t m;
    uint64_t im;
};

template<uint32_t Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template<std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_% mod()) {}
    template<std::signed_integral T>
    constexpr DynModInt(T x_) {
        int v = x_;
        v %= int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(uint32_t m) {
        bt = m;
    }

    static uint32_t mod() {
        return bt.mod();
    }

    constexpr uint32_t val() const {
        return x;
    }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt& operator*=(const DynModInt& rhs)& {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt& operator+=(const DynModInt& rhs)& {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt& operator-=(const DynModInt& rhs)& {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt& operator/=(const DynModInt& rhs)& {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream& operator>>(std::istream& is, DynModInt& a) {
        int64_t i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const DynModInt& a) {
        return os << a.val();
    }

    friend constexpr std::strong_ordering operator<=>(DynModInt lhs, DynModInt rhs) {
        return lhs.val() <=> rhs.val();
    }

    constexpr uint32_t operator()() const {
        return val();
    }

    struct Formatter {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        template <typename FormatContext>
        auto format(const DynModInt& x, FormatContext& ctx) const {
            return std::format_to(ctx.out(), "{}", x());
        }
    };

private:
    uint32_t x;
    static Barrett bt;
};

template<uint32_t Id>
Barrett DynModInt<Id>::bt = 998244353;
template<uint32_t Id>
struct std::formatter<DynModInt<Id>> : DynModInt<Id>::Formatter {};

using modint = DynModInt<0>;

using mint = modint998244353;