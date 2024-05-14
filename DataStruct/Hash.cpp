using i64 = long long;
constexpr i64 power(i64 base, i64 exp) {
    i64 res{ 1 };
    for (; exp; exp /= 2, base = base * base % P) {
        if (exp % 2) {
            res = (res * base % P);
        }
    }
    return res;
}

constexpr bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

constexpr int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
const int P = findPrime(rnd() % 900000000 + 100000000);
const int B = findPrime(rnd() % P);
const int R = power(B, P - 2);

constexpr int N = 100000;
int p[N + 1];
int q[N + 1];

struct Hash {
    int val;
    int siz;
    Hash(int val = 0, int siz = 0) : val(val), siz(siz) {}
    constexpr friend Hash operator+(const Hash& a, const Hash& b) {
        return Hash((a.val + 1LL * b.val * p[a.siz] % P) % P, a.siz + b.siz);
    }
    constexpr friend Hash operator-(const Hash& a, const Hash& b) {
        return Hash(i64(P - b.val + a.val) * q[b.siz] % P, a.siz - b.siz);
    }
    constexpr friend bool operator==(const Hash& a, const Hash& b) {
        return a.val == b.val;
    }
};

void initHash() {
    p[0] = 1;
    for (int i = 1; i <= N; i++) {
        p[i] = (1LL * p[i - 1] * B) % P;
    }
    q[0] = 1;
    for (int i = 1; i <= N; i++) {
        q[i] = (1LL * q[i - 1] * R) % P;
    }
}