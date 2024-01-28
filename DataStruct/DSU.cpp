class DSU {
private:
    std::vector<int> p, siz;
public:
    explicit DSU() {}
    explicit DSU(int n) { init(n); }
    constexpr void init(int n) {
        p.assign(n, 0);
        siz.assign(n, 1);
        std::iota(p.begin(), p.end(), 0);
    }
    constexpr int operator[] (int x) {
        return find(x);
    }
    constexpr int size(int i) {
        return siz[find(i)];
    }
    constexpr bool same(int x, int y) {
        return find(x) == find(y);
    }
    constexpr int find(int x) {
        while (p[x] != x) {
            x = p[x] = p[p[x]];
        }
        return x;
    }
    constexpr bool merge(int x, int y, int flag = true) {
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