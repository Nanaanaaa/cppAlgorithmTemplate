template<class T>
class Comb {
private:
    inline static int n = 0;
    inline static std::vector<T> _fac{ 1 };
    inline static std::vector<T> _invfac{ 1 };
    inline static std::vector<T> _inv{};
public:
    static void init(int m) {
        if (m <= n) {
            return;
        }

        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    static void extend(int m) {
        if (m > n) {
            init(2 * m);
        }
    }
    static T fac(int m) {
        extend(m);
        return m < 0 ? 0 : _fac[m];
    }
    static T invfac(int m) {
        extend(m);
        return m < 0 ? 0 : _invfac[m];
    }
    static T inv(int m) {
        extend(m);
        return m < 0 ? 0 : _inv[m];
    }
    static T binom(int n, int m) {
        return (n < m || m < 0) ? 0 : fac(n) * invfac(m) * invfac(n - m);
    }
    static T perm(int n, int m) {
        return (n < m || m < 0) ? 0 : fac(n) * invfac(n - m);
    }
};

using comb = Comb<mint>;