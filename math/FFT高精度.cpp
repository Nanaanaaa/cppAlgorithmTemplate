using db = long double;

struct comp {
    db x, y;
    comp(db real = 0, db imag = 0) : x(real), y(imag) {};
    comp operator+(const comp& b) const { return { x + b.x, y + b.y }; }
    comp operator-(const comp& b) const { return { x - b.x, y - b.y }; }
    comp operator*(const comp& b) const { return { x * b.x - y * b.y, x * b.y + y * b.x }; }
};

const db pi = acosl(-1.L);
std::vector<comp> fft_init(int L) {
    std::vector<comp> w(L, 1);
    for (int i = 2; i < L; i *= 2) {
        auto w0 = w.begin() + i / 2, w1 = w.begin() + i;
        comp wn(cosl(pi / i), sinl(pi / i));
        for (int j = 0; j < i; j += 2) {
            w1[j] = w0[j / 2];
            w1[j + 1] = w1[j] * wn;
        }
    }
    return w;
}

auto W = fft_init(1 << 20); // Notice !

void dft(std::vector<comp>& a) {
    comp x, y;
    const int n = a.size();
    for (int k = n / 2; k; k /= 2) {
        for (int i = 0; i < n; i += k * 2) {
            for (int j = 0; j < k; j++) {
                x = a[i + j], y = a[i + j + k];
                a[i + j + k] = (a[i + j] - y) * W[k + j], a[i + j] = x + y;
            }
        }
    }
}

void idft(std::vector<comp>& a) {
    const int n = a.size();
    comp x, y;
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += k * 2) {
            for (int j = 0; j < k; j++) {
                x = a[i + j], y = a[i + j + k] * W[k + j];
                a[i + j + k] = x - y, a[i + j] = x + y;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        a[i].x /= n;
        a[i].y /= n;
    }
    std::reverse(a.begin() + 1, a.end());
}

template<class T>
struct Poly : public std::vector<T> {
    Poly() : std::vector<T>() {}
    explicit constexpr Poly(int n) : std::vector<T>(n) {}
    explicit constexpr Poly(const std::vector<T>& a) : std::vector<T>(a) {}
    constexpr Poly(const std::initializer_list<T>& a) : std::vector<T>(a) {}

    constexpr static int norm(int n) {
        return 1 << (std::__lg(n - 1) + 1);
    }

    constexpr friend Poly operator+(const Poly& a, const Poly& b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
        return res;
    }
    constexpr friend Poly operator-(const Poly& a, const Poly& b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
        return res;
    }

    constexpr friend Poly operator*(i64 k, const Poly& a) {
        Poly ans{};
        for (auto i : a) {
            ans.push_back(k * i);
        }
        return ans;
    }

    constexpr friend Poly operator*(const Poly& a, const Poly& b) {
        int n = a.size() + b.size() - 1;
        std::vector<comp> c(norm(n));
        for (int i = 0; i < a.size(); i++) {
            c[i].x = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            c[i].y = b[i];
        }
        dft(c);
        for (auto& x : c) {
            x = x * x;
        }
        idft(c);
        Poly ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = T(c[i].y * .5L + .5L);
        }
        return ans;
    }

    constexpr Poly& operator*=(const Poly& b) {
        return (*this) = (*this) * b;
    }
};