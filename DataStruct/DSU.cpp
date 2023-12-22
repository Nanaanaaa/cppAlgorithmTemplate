class DSU {
private:
    std::vector<int> p, siz;
public:
    DSU() {}
    DSU(int n) { init(n); }
    ~DSU() {
        p.clear();
        p.shrink_to_fit();
        siz.clear();
        siz.shrink_to_fit();
    }
    void init(int n) {
        p.assign(n, 0);
        siz.assign(n, 1);
        std::iota(p.begin(), p.end(), 0);
    }
    constexpr int operator[] (int x) {
        return find(x);
    }
    int size(int i) {
        return siz[find(i)];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int find(int x) {
        while (p[x] != x) {
            x = p[x] = p[p[x]];
        }
        return x;
    }
    bool merge(int x, int y, int flag = true) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (flag && siz[x] < siz[y]) {
            std::swap(x, y);
        }
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
};