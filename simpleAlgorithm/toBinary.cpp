auto toBinary = [&](ll x) {
    std::vector<int> a;
    while (x) {
        a.push_back(x % 2);
        x /= 2;
    }
    std::reverse(a.begin(), a.end());
    return a;
};