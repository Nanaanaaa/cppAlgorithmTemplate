int gauss(std::vector<std::vector<double>>& a) {
    const int n = a.size();
    int c = 0, r = 0;
    for (; c < n; c++) {
        int t = r;
        for (int i = r; i < n; i++) {
            if (std::fabs(a[i][c]) > std::fabs(a[t][c])) {
                t = i;
            }
        }
        if (std::fabs(a[t][c]) < eps) {
            continue;
        }

        for (int j = c; j <= n; j++) {
            std::swap(a[r][j], a[t][j]);
        }

        for (int j = n; j >= c; j--) {
            a[r][j] /= a[r][c];
        }

        for (int i = r + 1; i < n; i++) {
            if (std::fabs(a[i][c]) > eps) {
                for (int j = n; j >= c; j--) {
                    a[i][j] -= a[r][j] * a[i][c];
                }
            }
        }
        r++;
    }

    if (r < n) {
        for (int i = r; i < n; i++) {
            if (std::fabs(a[i][n]) > eps) {
                return 1;
            }
        }
        return 2;
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                a[i][n] -= a[i][j] * a[j][n];
            }
        }
    }
    return 0;
}