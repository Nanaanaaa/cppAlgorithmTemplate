template<class T>
struct MST {
    const int n;
    struct Edge {
        int a, b;
        T w;
        Edge(int a, int b, T w): a(a), b(b), w(w) {}
        bool operator< (const Edge& e) const { return w < e.w; }
    };

    struct DSU {
        T ans = 0;
        std::vector<int> p, sz;
        DSU(int n): p(n), sz(n, 1) { std::iota(p.begin(), p.end(), 0); }
        int find(int x) {
            if (p[x] == x) return x;
            return p[x] = find(p[x]);
        }
        bool equal(int x, int y) { return find(x) == find(y); }
        bool merge(int x, int y, T w) {
            int px = find(x);
            int py = find(y);
            if (px == py) return false;
            ans += w;
            sz[py] += sz[px];
            p[px] = py;
            return true;
        }
        int size(int x) { return sz[find(x)]; }
    } dsu;

    std::vector<Edge> e;
    MST(int n):n(n), dsu(n) {}

    void add(int u, int v, T w) {
        e.emplace_back(u, v, w);
    }

    bool kruskal() {
        std::sort(e.begin(), e.end());
        int cnt = 0;
        for (auto [u, v, w] : e) {
            if (dsu.merge(u, v)) {
                cnt++;
            }
        }
        return cnt == n - 1;
    }

    T ans() { return dsu.ans; }
};
