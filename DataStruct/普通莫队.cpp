constexpr int M = 500;

constexpr int bel(int i) {
    return i / M;
}

std::sort(qry.begin(), qry.end(), [&](const auto& a, const auto& b) {
    if (a[0] / M != b[0] / M) return a[0] < b[0];
    return a[0] / M % 2 ? a[1] > b[1] : a[1] < b[1];
});

int l = 1, r = 0, res = 0;
std::vector<int> ans(m);

auto add = [&](int i) {

};
auto del = [&](int i) {

};

for (auto [x, y, i] : qry) {
    while (l < x) del(l++);
    while (l > x) add(--l);
    while (r < y) add(++r);
    while (r > y) del(r--);
    ans[i] = res;
}