#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = int64_t;

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
    int n = 0;
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
    mint64 ip(int m);
    mint64 p(int m) {
        if (m > n) {
            init(2 * m);
        }
        return m < 0 ? ip(-m) : _p[m];
    }
    mint64 ip(int m) {
        if (m > n) {
            init(2 * m);
        }
        return m < 0 ? p(-m) : _ip[m];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, n, a, b;
    std::cin >> n >> m >> a >> b;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }

    std::vector pre_s(n + 1, std::vector<mint64>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pre_s[i + 1][j + 1] = pre_s[i + 1][j] + pre_s[i][j + 1] - pre_s[i][j] + s[i][j] * coef::p(i * m + j);
        }
    }

    std::unordered_set<uint64_t> set;
    for (int i = 0; i + a <= n; i++) {
        for (int j = 0; j + b <= m; j++) {
            mint64 v = pre_s[i + a][j + b] - pre_s[i][j + b] - pre_s[i + a][j] + pre_s[i][j];
            v *= coef::ip(i * m + j);
            set.insert(v.val());
        }
    }

    int q;
    std::cin >> q;

    for (int _ = 0; _ < q; _++) {
        std::vector<std::string> t(a);
        for (int i = 0; i < a; i++) {
            std::cin >> t[i];
        }

        std::vector pre_t(a + 1, std::vector<mint64>(b + 1));
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                pre_t[i + 1][j + 1] = pre_t[i + 1][j] + pre_t[i][j + 1] - pre_t[i][j] + t[i][j] * coef::p(i * m + j);
            }
        }

        std::cout << set.contains(pre_t[a][b].val()) << '\n';
    }

    return 0;
}