template <class T, std::size_t N>
struct Matrix : std::array<std::array<T, N>, N> {
    constexpr Matrix& operator*=(const Matrix& r) {
        Matrix res{};
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    res[i][j] += (*this)[k][j] * r[i][k];
                }
            }
        }
        *this = std::move(res);
        return *this;
    }

    friend constexpr Matrix operator*(const Matrix& l, const Matrix& r) {
        Matrix res = l;
        res *= r;
        return res;
    }
};