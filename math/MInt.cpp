using u32 = unsigned;
using u64 = unsigned long long;
template<typename T>
constexpr T power(T base, u64 exp) {
    T res{ 1 };
    for (; exp != 0; exp /= 2, base *= base) {
        if (exp & 1) {
            res *= base;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
    requires std::unsigned_integral<U>
class ModIntBase {
public:
    constexpr ModIntBase() : x{ 0 } {}

    template<typename T>
        requires std::integral<T>
    constexpr ModIntBase(T x_) : x{ norm(x_ % T {P}) } {}

    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }
    constexpr ModIntBase operator+() const {
        return *this;
    }
    constexpr ModIntBase& operator++() {
        x++;
        if (x == P) {
            x = 0;
        }
        return *this;
    }
    constexpr ModIntBase& operator--() {
        if (x == 0) {
            x = P;
        }
        x--;
        return *this;
    }
    constexpr ModIntBase operator++(int) {
        ModIntBase result = *this;
        ++*this;
        return result;
    }
    constexpr ModIntBase operator--(int) {
        ModIntBase result = *this;
        --*this;
        return result;
    }

    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }

    constexpr ModIntBase& operator*=(const ModIntBase& rhs)& {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }

    constexpr ModIntBase& operator+=(const ModIntBase& rhs)& {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr ModIntBase& operator-=(const ModIntBase& rhs)& {
        x = norm(x - rhs.x);
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

    friend constexpr std::ostream& operator<<(std::ostream& os, const ModIntBase& a) {
        return os << a.val();
    }

    friend constexpr std::istream& operator>>(std::istream& is, ModIntBase& a) {
        return is >> a.x;
    }

    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }

    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }

    friend constexpr bool operator>(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() > rhs.val();
    }
private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr u32 P = 998244353;
using mint = ModInt<P>;
template<>
struct std::formatter<mint> {
    constexpr auto parse(const std::format_parse_context& ctx) {
        return ctx.begin();
    }

    constexpr auto format(const mint& x, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", x.val());
    }
};