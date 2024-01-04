constexpr int P = 998244353;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template<int P = ::P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{ norm(x % getMod()) } {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        }
        else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt& operator*() const {
        return *this;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MInt& operator*=(MInt rhs)& {
        x = 1LL * x * rhs.x % getMod();
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
    constexpr MInt& operator^=(i64 rhs)& {
        *this = power(*this, rhs);
        return *this;
    }

    template <class T>
    constexpr MInt& operator*=(T rhs)& {
        *this *= MInt(rhs);
        return *this;
    }
    template <class T>
    constexpr MInt& operator+=(T rhs)& {
        *this += MInt(rhs);
        return *this;
    }
    template <class T>
    constexpr MInt& operator-=(T rhs)& {
        *this -= MInt(rhs);
        return *this;
    }
    template <class T>
    constexpr MInt& operator/=(T rhs)& {
        *this /= MInt(rhs);
        return *this;
    }

    constexpr MInt& operator++()& {
        return *this += 1;
    }
    constexpr MInt& operator++(int)& {
        auto res = *this;
        ++*this;
        return res;
    }
    constexpr MInt& operator--()& {
        return *this -= 1;
    }
    constexpr MInt& operator--(int)& {
        auto res = *this;
        --*this;
        return res;
    }

    template <class T, class U>
    friend constexpr MInt operator*(T lhs, U rhs) {
        MInt res = MInt(lhs);
        res *= rhs;
        return res;
    }
    template <class T, class U>
    friend constexpr MInt operator+(T lhs, U rhs) {
        MInt res = MInt(lhs);
        res += rhs;
        return res;
    }
    template <class T, class U>
    friend constexpr MInt operator-(T lhs, U rhs) {
        MInt res = MInt(lhs);
        res -= rhs;
        return res;
    }
    template <class T, class U>
    friend constexpr MInt operator/(T lhs, U rhs) {
        MInt res = MInt(lhs);
        res /= rhs;
        return res;
    }
    template <class T>
    friend constexpr MInt operator^(T lhs, i64 rhs) {
        MInt res = MInt(lhs);
        res ^= rhs;
        return res;
    }

    friend constexpr std::istream& operator>>(std::istream& is, MInt& a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os, const MInt& a) noexcept {
        return os << a.val();
    }
    template <class T, class U>
    friend constexpr MInt operator==(T lhs, U rhs) {
        MInt t1 = MInt(lhs);
        MInt t2 = MInt(rhs);
        return t1.val() == t2.val();
    }
    template <class T, class U>
    friend constexpr MInt operator!=(T lhs, U rhs) {
        MInt t1 = MInt(lhs);
        MInt t2 = MInt(rhs);
        return t1.val() != t2.val();
    }
};

template<>
int MInt<0>::Mod = ::P;

template<int V, int P = ::P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

template<int P = ::P>
constexpr MInt<P> Z1 = MInt<P>(1);

using Z = MInt<>;