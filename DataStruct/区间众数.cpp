std::vector<std::array<int, 3>> qry(q);
for (int i = 0; i < q; i++) {
    int l, r;
    std::cin >> l >> r;
    l--;
    r--;
    qry[i] = { l, r, i };
}

std::sort(qry.begin(), qry.end(), [&](const auto& a, const auto& b) {
    if (a[0] / M != b[0] / M) return a[0] < b[0];
    return a[0] / M % 2 ? a[1] > b[1] : a[1] < b[1];
});

std::vector<int> ans(q);
int l = 1, r = 0;

std::vector<int> cnt(n), freq(n + 1);
int res = 0;
auto add = [&](int i) {
    i = c[i];
    if (++freq[++cnt[i]] == 1) {
        res++;
    }
};
auto del = [&](int i) {
    i = c[i];
    if (--freq[cnt[i]--] == 0) {
        res--;
    }
};

for (auto [x, y, i] : qry) {
    while (l < x) del(l++);
    while (l > x) add(--l);
    while (r < y) add(++r);
    while (r > y) del(r--);
    ans[i] = res;
}
