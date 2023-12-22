std::vector<int> minp, primes, minpe;

void sieve(int n) {
    minp.assign(n + 1, 0);
    minpe.assign(n + 1, 0);
    primes.clear();

    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            minpe[i] = i;
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            minpe[i * p] = p;
            if (p == minp[i]) {
                minpe[i * p] = minpe[i] * p;
                break;
            }
        }
    }
}