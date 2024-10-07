using i128 = __int128;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

constexpr i64 power(i64 a, i64 b, i64 P = 998244353) {
    i64 res = 1;
    for (; b; b /= 2, a = (i128)a * a % P) {
        if (b % 2) {
            res = (i128)res * a % P;
        }
    }
    return res;
}

struct PollardRho {
    i64 maxFactor;
    PollardRho(i64 n) :maxFactor{} { work(n); }
    bool millerRabin(i64 p) { // 判断素数 
        if (p < 2) return false;
        if (p == 2) return true;
        if (p == 3) return true;
        i64 d = p - 1, r = 0;
        while (d % 2 == 0) { // 将d处理为奇数
            r++;
            d /= 2;
        }
        for (i64 k = 0; k < 10; k++) {
            i64 a = 1LL * rnd() % (p - 2) + 2;
            i64 x = power(a, d, p);
            if (x == 1 || x == p - 1) continue;
            for (int i = 0; i < r - 1; i++) {
                x = (i128)x * x % p;
                if (x == p - 1) break;
            }
            if (x != p - 1) return false;
        }
        return true;
    }

    i64 pollardRho(i64 x) {
        i64 s = 0, t = 0;
        i64 c = 1LL * rnd() % (x - 1) + 1;
        for (i64 goal = 1, val = 1;; goal *= 2, s = t, val = 1) {  // 倍增优化
            for (int step = 1; step <= goal; step++) {
                t = ((i128)t * t + c) % x;
                val = (i128)val * std::abs(t - s) % x;
                if (step % 127 == 0) {
                    i64 d = std::gcd(val, x);
                    if (d > 1) return d;
                }
            }
            i64 d = std::gcd(val, x);
            if (d > 1) return d;
        }
    }

    void work(i64 x) {
        if (x <= maxFactor || x < 2) return;
        if (millerRabin(x)) {              // 如果x为质数
            maxFactor = std::max(maxFactor, x);  // 更新答案
            return;
        }
        i64 p = x;
        while (p >= x) p = pollardRho(x);  // 使用该算法
        while (x % p == 0) x /= p;
        work(x), work(p);  // 继续向下分解x和p
    }
};