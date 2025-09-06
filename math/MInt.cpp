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

inline constexpr mint operator "" _Z(unsigned long long v) {
    return mint(v);
}
inline constexpr mint operator "" _z(unsigned long long v) {
    return mint(v);
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