std::vector<int> minp, primes, mu;

void sieve(int n) {
    minp.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();

    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            mu[i] = -1;
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            mu[i * p] = -mu[i];
            if (p == minp[i]) {
                mu[i * p] = 0;
                break;
            }
        }
    }
}
