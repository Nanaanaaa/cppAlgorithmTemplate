template<class T = int>
struct Matrix {
    int n, m;
    int rnk = -1;
    std::vector<std::vector<T>> mat;
    constexpr Matrix() :n(0), m(0) {}
    constexpr Matrix(int n) : n(n), m(n) {
        mat.assign(n, std::vector<T>(n));
    }
    constexpr Matrix(int n, int m) : n(n), m(m) {
        mat.assign(n, std::vector<T>(m));
    }
    constexpr Matrix(const std::vector<std::vector<T>>& mat) : n(mat.size()), m(mat.front().size()) {
        this->mat = mat;
    }
    constexpr Matrix(const std::vector<T>& init) {
        n = m = std::sqrt(init.size());
        mat.assign(n, std::vector<T>(m));
        for (int i = 0, k = 0; i < n; i++) {
            for (int j = 0; j < m; j++, k++) {
                mat[i][j] = init[k];
            }
        }
    }
    constexpr Matrix(int n_, const std::vector<T>& init) {
        n = m = n_;
        mat.assign(n, std::vector<T>(m));
        for (int i = 0, k = 0; i < n; i++) {
            for (int j = 0; j < m; j++, k++) {
                mat[i][j] = init[k];
            }
        }
    }
    constexpr Matrix(int n, int m, const std::vector<T>& init) {
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

    constexpr Matrix& operator*=(const Matrix& b) {
        Matrix c(this->n, b.m);
        assert(this->m == b.n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                auto r = mat[i][k];
                for (int j = 0; j < b.m; j++) {
                    c.mat[i][j] += b.mat[k][j] * r;
                }
            }
        }
        mat = std::move(c.mat);
        return *this;
    }

    constexpr Matrix& operator*=(i64 k) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mat[i][j] *= k;
            }
        }
        return *this;
    }

    constexpr friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        Matrix res = lhs;
        res *= rhs;
        return res;
    }
    constexpr friend Matrix operator*(T k, const Matrix& rhs) {
        Matrix res = rhs;
        res *= k;
        return res;
    }
    constexpr friend Matrix operator*(const Matrix& lhs, T k) {
        Matrix res = lhs;
        res *= k;
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

    constexpr friend std::ostream& operator<<(std::ostream& os, const Matrix& M) {
        for (auto it : M.mat) {
            for (int i = 0; i < it.size(); i++) {
                os << it[i] << " \n"[i + 1 == it.size()];
            }
        }
        return os;
    }

    constexpr auto& begin() {
        return mat.begin();
    }
    constexpr auto& end() {
        return mat.end();
    }

    const int rank() {
        rref();
        return rnk;
    }

    Matrix rref() {
        Matrix a = *this;
        rnk = 0;
        for (int row = 0, col = 0; row < n && col < m; row++, rnk++) {
            while (col < m && a[row][col] == 0) {
                col++;
            }
            if (col == m) {
                break;
            }
            assert(row < n && col < m);
            assert(a[row][col] != 0);
            for (int i = m - 1; i >= col; i--) {
                a[row][i] /= a[row][col];
            }

            for (int i = 0; i < n; i++) {
                if (i == row) continue;
                T k = a[i][col];
                for (int j = col; j < m; j++) {
                    a[i][j] -= k * a[row][j];
                }
            }
        }
        return a;
    }
};
