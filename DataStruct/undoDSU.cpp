struct UndoDSU {
    int n;
    std::vector<int> p, siz, rank;
    std::vector<std::tuple<int, int, int>> stk;
    
    UndoDSU(int n) :n(n), p(n), siz(n, 1), rank(n) {
        std::iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) {
            return x;
        }
        return find(p[x]);
    }

    bool equal(int x, int y) {
        return find(x) == find(y);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return;
        }
        if (rank[x] < rank[y]) {
            std::swap(x, y);
        }
        siz[x] += y;
        p[y] = x;
        stk.emplace_back(x, y, rank[x] == rank[y]);
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }

    void undo() {
        auto [x, y, e] = stk.back();
        rank[x] -= e;
        p[y] = y;
        stk.pop_back();
    }
};