template<class T>
struct Matrix {
    int n;
    std::vector<std::vector<T>> mat;
    Matrix() {}
    Matrix(int n) :n(n) {
        mat.assign(n, std::vector<T>(n));
    }
    Matrix(std::vector<std::vector<T>> mat) :n(mat.size()) {
        this->mat = mat;
    }
    Matrix(std::vector<T> init) {
        n = std::sqrt(init.size());
        mat.assign(n, {});
        for (int i = 0, k = 0; i < n; i++) {
            for (int j = 0; j < n; j++, k++) {
                mat[i][j] = init[k];
            }
        }
    }

    Matrix& operator+=(const Matrix& rhs) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
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

    Matrix& operator-=(const Matrix& rhs) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
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


    Matrix& operator*=(const Matrix& rhs) {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                auto r = mat[i][k];
                for (int j = 0; j < n; j++) {
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

    Matrix& operator ^=(i64 k) {
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
    constexpr friend Matrix operator ^(const Matrix& lhs, i64 k) {
        Matrix res = lhs;
        res ^= k;
        return res;
    }
};