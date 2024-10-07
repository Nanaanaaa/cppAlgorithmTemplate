constexpr int N = 205;

std::bitset<N> A[N];

int gauss(int n, int m) {
    int c = 0, r = 0, p = 0;
    for (; c < n; c++) {
        for (p = r; p < n; p++) {
            if (A[p][c]) {
                break;
            }
        }
        if (!A[p][c]) {
            continue;
        }

        std::swap(A[r], A[p]);

        for (int i = r + 1; i < n; i++) {
            if (A[i][c]) {
                A[i] ^= A[r];
            }
        }
        r++;
    }

    if (r < n) {
        for (int i = r; i < n; i++) {
            if (A[i][n]) {
                return -1;
            }
        }
        return n - r;
    }
    else {
        for (int i = n - 1; i >= 0; i--) {
            int t = A[i][n];
            for (int j = i + 1; j < n; j++) {
                t ^= A[i][j] & A[j][n];
            }
            A[i][n] = t;
        }
    }
    return 0;
}