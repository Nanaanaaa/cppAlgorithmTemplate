namespace comb {
    int n;
    std::vector<Z> _fac{ 1 };
    std::vector<Z> _invfac{ 1 };
    std::vector<Z> _inv;

    void init(int m) {
        m = std::min(m, Z::getMod() - 1);
        if (m <= n) return;
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

    Z fac(int m) {
        if (m < 0) return 0;
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m < 0) return 0;
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m < 0) return 0;
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
    Z perm(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(n - m);
    }
};