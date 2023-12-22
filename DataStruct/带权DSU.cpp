struct DSU {
    std::vector<int> p, siz;
    std::vector<i64> d;
    DSU(int n) : p(n), siz(n, 1), d(n) {
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) {
            return x;
        }
        int t = p[x];
        p[x] = find(p[x]);
        d[x] += d[t];
        return p[x];
    }
    bool equal(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y, int v) {
        int px = find(x), py = find(y);
        if (px == py) {
            return d[y] == d[x] + v;
        }
        d[py] = d[x] - d[y] + v;
        siz[px] += siz[py];
        p[py] = px;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};