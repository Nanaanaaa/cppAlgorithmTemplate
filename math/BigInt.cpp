constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template <class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z& operator*=(const Z& rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z& operator+=(const Z& rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z& operator-=(const Z& rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z& operator/=(const Z& rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream& operator>>(std::istream& is, Z& a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Z& a) {
        return os << a.val();
    }
};

std::vector<int> rev;
std::vector<Z> roots{ 0, 1 };
void dft(std::vector<Z>& a) {
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
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            Z e = power(Z(3), (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
void idft(std::vector<Z>& a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - P) / n;
    for (int i = 0; i < n; i++)
    {
        a[i] *= inv;
    }
}
struct BigInt
{
    std::vector<Z> a;
    BigInt() :a{ 0 } {
        a.resize(1);
    }
    BigInt(const int& x) : a{ x }
    {
        norm();
    }
    BigInt(const std::vector<Z>& a) : a(a)
    {
        norm();
    }
    BigInt(const std::initializer_list<Z>& a) : a(a)
    {
        norm();
    }
    int size() const
    {
        return a.size();
    }
    void resize(int n)
    {
        a.resize(n);
    }
    Z operator[](int idx) const
    {
        if (idx < size())
        {
            return a[idx];
        }
        else
        {
            return 0;
        }
    }
    Z& operator[](int idx)
    {
        return a[idx];
    }
    BigInt norm()
    { // 十进制进位
        for (int i = 1; i < int(a.size()); i++)
        {
            a[i] += a[i - 1].val() / 10;
            a[i - 1] = a[i - 1].val() % 10;
        }
        while (!a.empty() && (*a.rbegin()).val() >= 10)
        {
            a.push_back(a[a.size() - 1].val() / 10);
            a[(int)a.size() - 2] = a[(int)a.size() - 2].val() % 10;
        }
        return *this;
    }
    friend BigInt operator+(const BigInt& a, const BigInt& b)
    {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++)
        {
            res[i] = a[i] + b[i];
        }

        return BigInt(res).norm();
    }
    friend BigInt operator-(const BigInt& a, const BigInt& b)
    {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++)
        {
            res[i] = a[i] - b[i];
        }
        return BigInt(res).norm();
    }
    friend BigInt operator*(BigInt a, BigInt b)
    {
        if (a.size() == 0 || b.size() == 0)
        {
            return BigInt();
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot)
        {
            sz *= 2;
        }
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i)
        {
            a.a[i] = a[i] * b[i];
        }
        idft(a.a);
        a.resize(tot);
        return a.norm();
    }
    friend BigInt operator*(Z a, BigInt b)
    {
        for (int i = 0; i < int(b.size()); i++)
        {
            b[i] *= a;
        }
        return b.norm();
    }
    friend BigInt operator*(BigInt a, Z b)
    {
        for (int i = 0; i < int(a.size()); i++)
        {
            a[i] *= b;
        }
        return a.norm();
    }
    friend BigInt operator*(BigInt a, int b)
    {
        return a * Z(b);
    }
    friend BigInt operator*(int a, BigInt b)
    {
        return Z(a) * b;
    }
    friend BigInt operator/(BigInt a, int b)
    {//默认可以整除
        long long p = 0;
        bool flag = false;
        BigInt ans;
        ans.resize(a.size());
        for (int i = (int)a.size() - 1; i >= 0; i--)
        {
            p = p * 10 + a[i].val();
            ans[i] = p / b;
            p %= b;
            if (ans[i].val() > 0 && !flag)
                ans.resize(i + 1), flag = true;
        }
        if (!flag) //答案为0
            ans.resize(1);
        return ans;
    }
    BigInt& operator+=(BigInt b)
    {
        return (*this) = (*this) + b;
    }
    BigInt& operator-=(BigInt b)
    {
        return (*this) = (*this) - b;
    }
    BigInt& operator*=(BigInt b)
    {
        return (*this) = (*this) * b;
    }
    BigInt& operator*=(int b)
    {
        return (*this) = (*this) * b;
    }
    BigInt& operator/=(int b)
    {
        return (*this) = (*this) / b;
    }
    friend std::istream& operator>>(std::istream& is, BigInt& a)
    {
        std::string s;
        is >> s;
        a.resize(s.length());
        for (int i = s.length() - 1; i >= 0; i--)
            a[i] = s[s.length() - 1 - i] - '0';
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInt& a)
    {
        for (int i = int(a.size()) - 1; i >= 0; i--)
            os << a[i].val();
        return os;
    }
    friend bool operator<(const BigInt& a, const BigInt& b)
    {
        if (a.size() != b.size())
            return a.size() < b.size();
        else
        {
            for (int i = int(a.size()) - 1; i >= 0; i--)
            {
                if (a[i].val() != b[i].val())
                    return a[i].val() < b[i].val();
            }
        }
        return false;
    }
    friend bool operator>(const BigInt& a, const BigInt& b)
    {
        return b < a;
    }
    friend bool operator==(const BigInt& a, const BigInt& b)
    {
        if (a.size() != b.size())
        {
            return a.size() < b.size();
        }
        else
        {
            for (int i = (int)a.size() - 1; i >= 0; i--)
            {
                if (a[i].val() != b[i].val())
                {
                    return a[i].val() < b[i].val();
                }
            }
        }
        return true;
    }
    friend bool operator<=(const BigInt& a, const BigInt& b)
    {
        return (a < b) || (b == a);
    }
    friend bool operator>=(const BigInt& a, const BigInt& b)
    {
        return (a > b) || (b == a);
    }
    friend bool operator!=(const BigInt& a, const BigInt& b)
    {
        return (a > b) || (a < b);
    }
};