namespace comb {
    constexpr int N = 1e6;
    int P;

    bool is_init;
    int _fac[N + 1], _ifac[N + 1];

    constexpr i64 power(i64 a, i64 b) {
        i64 res = 1;
        for (; b; b /= 2, a = a * a % P) {
            if (b % 2) {
                res = res * a % P;
            }
        }
        return res;
    }

    void init(int N = comb::N) {
        _fac[0] = 1;
        for (int i = 1; i <= N; i++) {
            _fac[i] = 1LL * _fac[i - 1] * i % P;
        }
        _ifac[N] = power(_fac[N], P - 2);
        for (int i = N; i >= 1; i--) {
            _ifac[i - 1] = 1LL * _ifac[i] * i % P;
        }
        is_init = true;
    }

    int fac(int n) {
        if (!is_init) init();
        return n < 0 ? 0 : _fac[n];
    }

    int ifac(int n) {
        if (!is_init) init();
        return n < 0 ? 0 : _ifac[n];
    }

    int perm(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1LL * fac(n) * ifac(n - m) % P;
    }

    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1LL * fac(n) * ifac(m) % P * ifac(n - m) % P;
    }

    int lucas(i64 n, i64 m) { // 使用前 init(P - 1);
        if (n < m || m < 0) return 0;
        if (m == 0) return 1;
        return 1LL * binom(n % P, m % P) * lucas(n / P, m / P) % P; // assume P is prime 
    }
}
using namespace comb;