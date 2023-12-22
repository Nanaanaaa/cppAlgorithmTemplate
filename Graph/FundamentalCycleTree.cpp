struct FundamentalCycleTree {
    const int n;
    std::vector<int> nxt, vis, incyc;
    std::vector<std::vector<int>> cyc;
    FundamentalCycleTree(int n) :n(n), nxt(n, -1), vis(n, -1), incyc(n) {}

    void addEdge(int i, int j) {
        nxt[i] = j;
    }

    std::vector<std::vector<int>> work() {
        for (int i = 0; i < n; i++) {
            if (vis[i] != -1) {
                continue;
            }
            int u = i;
            while (vis[u] == -1) {
                vis[u] = i;
                u = nxt[u];
            }
            std::vector<int> p;
            while (!incyc[u] && vis[u] == i) {
                p.push_back(u);
                incyc[u] = true;
                u = nxt[u];
            }
            if (!p.empty()) {
                cyc.push_back(p);
            }
        }
        return cyc;
    }
};