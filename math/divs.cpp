std::vector<int> getdivs(int n) { // 不含1和 n
    std::vector<int> divs;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (n / i != i) {
                divs.push_back(n / i);
            }
        }
    }
    return divs;
}