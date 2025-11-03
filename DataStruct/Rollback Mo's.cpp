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

std::vector<int> bel(n), L(n), R(n);
for (int i = 0; i < n; i++) {
    bel[i] = i / M;
}
for (int i = 0; i < n; i++) {
    L[i] = std::min(n - 1, i * M);
    R[i] = std::min(n - 1, (i + 1) * M);
}

std::sort(qry.begin(), qry.end(), [&](const Query& a, const Query& b) {
    if (bel[a.l] != bel[b.l]) return a.l < b.l;
    return a.r < b.r;
});

std::vector<int> cnt(n), cnt__(n);
std::array<std::array<int, 2>, 2> res{}, res_{};
res.fill({ -1, -1 });
res_.fill({ -1, -1 });

auto maintain = [&](int i, auto& res, auto& cnt) {

};
auto add = [&](int i, auto& res) {
    i = a[i];
    cnt[i]++;
    maintain(i, res, cnt);
};
auto del = [&](int i) {
    i = a[i];
    cnt[i]--;
};

std::vector<std::vector<int>> ans(q);
int l = 0, r = -1;
int l_ = 0, last = -1;
for (auto [ql, qr, id] : qry) {
    if (bel[ql] == bel[qr]) {
        // brute force in [ql, qr], use__
        std::array<std::array<int, 2>, 2> res__{};
        res__.fill({ -1, -1 });
        for (auto i : stdv::iota(ql, qr + 1)) {
            i = a[i];
            cnt__[i]++;
            maintain(i, res__, cnt__);
        }
        // add res__ to ans
        for (auto i : stdv::iota(ql, qr + 1)) {
            i = a[i];
            cnt__[i]--;
        }
    } else {
        if (bel[ql] != last) {
            while (r > R[bel[ql]]) {
                del(r--);
            }
            while (l <= R[bel[ql]]) {
                del(l++);
            }
            //reset res
            res.fill({ -1, -1 });
            last = bel[ql];
        }

        while (r < qr) {
            add(++r, res);
        }
        res_ = res;
        l_ = l;

        while (l_ > ql) {
            add(--l_, res_);
        }
        // add res_ to ans
        ans[id] = res_;

        while (l_ < l) {
            del(l_++);
        }
    }
}