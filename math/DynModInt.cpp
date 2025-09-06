template<class T>
constexpr T power(T a, uint64_t e, T res = T(1)) {
    for (; e != 0; e >>= 1, a *= a) {
        if (e & 1) {
            res *= a;
        }
    }
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

class Barrett {
public:
    explicit Barrett(uint32_t m_) : m(m_), im((uint64_t)(-1) / m_ + 1) {
        assert(m_ >= 1);
    }

    constexpr uint32_t mod() const {
        return m;
    }

    constexpr uint32_t mul(uint32_t a, uint32_t b) const {
        uint64_t z = a;
        z *= b;

        uint64_t x = uint64_t((__uint128_t(z) * im) >> 64);

        uint32_t v = uint32_t(z - x * m);
        if (m <= v) {
            v -= m;
        }
        return v;
    }

private:
    uint32_t m;
    uint64_t im;
};

template<uint32_t Id>
class DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template<std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_% mod()) {}
    template<std::signed_integral T>
    constexpr DynModInt(T x_) {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(uint32_t m) {
        bt = Barrett(m);
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
    friend constexpr bool operator==(DynModInt lhs, DynModInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(DynModInt lhs, DynModInt rhs) {
        return lhs.val() != rhs.val();
    }

    constexpr DynModInt& operator++() {
        *this += 1;
        return *this;
    }

    constexpr DynModInt operator++(int) {
        DynModInt temp = *this;
        ++*this;
        return temp;
    }

    constexpr DynModInt& operator--() {
        *this -= 1;
        return *this;
    }

    constexpr DynModInt operator--(int) {
        DynModInt temp = *this;
        --*this;
        return temp;
    }

    constexpr uint32_t operator()() const {
        return val();
    }

    constexpr DynModInt pow(uint64_t e) const {
        return power(*this, e);
    }

    friend constexpr DynModInt operator^(DynModInt a, uint64_t e) {
        return power(a, e);
    }

    friend constexpr DynModInt pow(DynModInt a, uint64_t e) {
        return power(a, e);
    }
private:
    uint32_t x;
    inline static Barrett bt = Barrett(998244353);
};

using mint = DynModInt<0>;

inline constexpr mint operator "" _Z(unsigned long long v) {
    return mint(v);
}
inline constexpr mint operator "" _z(unsigned long long v) {
    return mint(v);
}

#if __cplusplus > 202002L
template<uint32_t Id>
struct std::formatter<DynModInt<Id>> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const DynModInt<Id>& x, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{}", x());
    }
};
#endif