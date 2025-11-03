constexpr int M = 500;

struct Query {
    int l, r, id;
};

std::vector<Query> qry(q);
for (int i = 0; i < q; i++) {
    int l, r;
    std::cin >> l >> r;
    qry[i] = { l - 1, r - 1, i };
}

std::vector<int> bel(n);
for (int i = 0; i < n; i++) {
    bel[i] = i / M;
}

std::sort(qry.begin(), qry.end(), [&](const Query& a, const Query& b) {
    if (bel[a.l] != bel[b.l]) return a.l < b.l;
    return bel[a.l] % 2 ? a.r > b.r : a.r < b.r;
});

int res = 0;
std::vector<int> ans(q);

auto add = [&](int i) {

};
auto del = [&](int i) {

};

int l = 0, r = -1;
for (auto [ql, qr, id] : qry) {
    while (l < ql) del(l++);
    while (l > ql) add(--l);
    while (r < qr) add(++r);
    while (r > qr) del(r--);
    ans[id] = res;
}