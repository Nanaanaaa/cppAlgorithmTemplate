struct BigInt {
    std::vector<int> v;
};

constexpr int P = 1E9;

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt c;
    c.v.resize(std::max(a.v.size(), b.v.size()) + 1);
    for (int i = 0; i < a.v.size(); i++) {
        c.v[i] += a.v[i];
    }
    for (int i = 0; i < b.v.size(); i++) {
        c.v[i] += b.v[i];
    }
    for (int i = 0; i < c.v.size(); i++) {
        if (c.v[i] >= P) {
            c.v[i] -= P;
            c.v[i + 1]++;
        }
    }
    if (c.v.back() == 0) {
        c.v.pop_back();
    }
    return c;
}

bool operator<(const BigInt& a, const BigInt& b) {
    if (a.v.size() != b.v.size()) {
        return a.v.size() < b.v.size();
    }
    for (int i = int(a.v.size()) - 1; i >= 0; i--) {
        if (a.v[i] != b.v[i]) {
            return a.v[i] < b.v[i];
        }
    }
    return false;
}

void print(const BigInt& a) {
    const auto& v = a.v;
    if (v.empty()) {
        std::cout << "0\n";
        return;
    }
    std::cout << v.back();
    for (int i = int(v.size()) - 2; i >= 0; i--) {
        std::cout << std::setw(9) << std::setfill('0') << v[i];
    }
    std::cout << "\n";
}