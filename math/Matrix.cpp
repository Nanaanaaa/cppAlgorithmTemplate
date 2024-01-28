template<class T = int>
struct Matrix {
    int n, m;
    std::vector<std::vector<T>> mat;
    Matrix() :n(0), m(0) {}
    Matrix(int n) :n(n), m(n) {
        mat.assign(n, std::vector<T>(n));
    }
    Matrix(int n, int m) :n(n), m(m) {
        mat.assign(n, std::vector<T>(m));
    }
    Matrix(const std::vector<std::vector<T>>& mat) :n(mat.size()), m(mat.front().size()) {
        this->mat = mat;
    }
    Matrix(const std::vector<T>& init) {
        n = m = std::sqrt(init.size());
        mat.assign(n, std::vector<T>(m));
        for (int i = 0, k = 0; i < n; i++) {
            for (int j = 0; j < m; j++, k++) {
                mat[i][j] = init[k];
            }
        }
    }
    Matrix(int n, int m, const std::vector<T>& init) {
        this->n = n;
        this->m = m;
        mat.assign(n, std::vector<T>(m));
        for (int i = 0, k = 0; i < n; i++) {
            for (int j = 0; j < m; j++, k++) {
                mat[i][j] = init[k];
            }
        }
    }

    constexpr Matrix& operator+=(const Matrix& rhs) {
        assert(this->n == rhs.n && this->m == rhs.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mat[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    constexpr friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        Matrix res = lhs;
        res += rhs;
        return res;
    }

    constexpr Matrix& operator-=(const Matrix& rhs) {
        assert(this->n == rhs.n && this->m == rhs.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mat[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    constexpr friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        Matrix res = lhs;
        res -= rhs;
        return res;
    }

    constexpr Matrix& operator*=(const Matrix& rhs) {
        Matrix res(n, m);
        assert(this->m == rhs.n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                auto r = mat[i][k];
                for (int j = 0; j < m; j++) {
                    res.mat[i][j] += rhs.mat[k][j] * r;
                }
            }
        }
        mat = std::move(res.mat);
        return *this;
    }

    constexpr friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        Matrix res = lhs;
        res *= rhs;
        return res;
    }

    constexpr Matrix& operator^=(i64 k) {
        assert(this->n == this->m);
        Matrix a = *this;
        Matrix b(n);
        for (int i = 0; i < n; i++) {
            b.mat[i][i] = 1;
        }
        for (; k; k /= 2, a *= a) {
            if (k % 2) {
                b *= a;
            }
        }
        mat = std::move(b.mat);
        return *this;
    }
    constexpr friend Matrix operator^(const Matrix& lhs, i64 k) {
        Matrix res = lhs;
        res ^= k;
        return res;
    }

    constexpr auto& operator[](int i) {
        return mat[i];
    }
};
