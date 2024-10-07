#include <bits/stdc++.h>

template<typename T, std::size_t N> std::istream& operator>>(std::istream& is, std::array<T, N>& v) { for (auto& i : v) is >> i; return is; }
template<typename T, std::size_t N> std::ostream& operator<<(std::ostream& os, std::array<T, N>& v) { for (auto& i : v) os << i << " "; return os; }
template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (auto& i : v) os << i << " "; return os; }
template<typename T> auto dbug(const std::initializer_list<T>& a) { std::cerr << "dbug: "; for (auto& i : a) std::cerr << i << " "; std::cerr << std::endl; }

using i64 = long long;

constexpr i64 power(i64 a, i64 b, i64 P = 998244353) {
    i64 res = 1;
    for (; b; b /= 2, a = a * a % P) {
        if (b % 2) {
            res = res * a % P;
        }
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int P;
    std::cin >> P;
    int m = P - 1;
    std::vector<int> b;
    for (int i = 2; i <= m / i; i++) {
        if (m % i == 0) {
            b.push_back(i);
            while (m % i == 0) m /= i;
        }
    }
    if (m != 1) {
        b.push_back(m);
    }
    for (int g = 1; g < P; g++) {
        bool valid = true;
        for (auto p : b) {
            if (power(g, (P - 1) / p, P) == 1) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << g << "\n";
            break;
        }
    }

    return 0;
}