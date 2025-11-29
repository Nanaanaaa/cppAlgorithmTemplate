struct DSU {
    int n;
    std::vector<int> f, siz;

    DSU() :n(0) {}
    explicit DSU(int n) :n(n) {
        init(n);
    }

    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    constexpr int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool merge(int x, int y, bool merge_by_size = true) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }

        if (merge_by_size && siz[y] > siz[x]) {
            std::swap(x, y);
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> p(n), psize(n);
        for (int i = 0; i < n; i++) {
            p[i] = find(i);
            psize[p[i]]++;
        }
        std::vector<std::vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i].reserve(psize[i]);
        }
        for (int i = 0; i < n; i++) {
            ans[p[i]].push_back(i);
        }
        std::erase_if(ans, [](const std::vector<int>& v) {
            return v.empty();
        });
        return ans;
    }

    constexpr int operator[](int i) {
        return find(i);
    }
};