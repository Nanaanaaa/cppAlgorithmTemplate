struct HLD {
    int n;
    int cur;
    std::vector<int> siz, top, dep, fa, in, out, seq;
    std::vector<std::vector<std::array<int, 2>>> adj;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        cur = 0;
        this->n = n;
        siz.assign(n, 0);
        top.assign(n, 0);
        dep.assign(n, 0);
        in.assign(n, 0);
        out.assign(n, 0);
        seq.assign(n, 0);
        fa.assign(n, 0);
        adj.assign(n, {});
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
    void work(int root = 0) {
        top[root] = root;
        fa[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        siz[u] = 1;
        for (auto& [v, w] : adj[u]) {
            if (fa[u] == v) continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0][0]]) {
                std::swap(v, adj[u][0][0]);
                std::swap(w, adj[u][0][1]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto& [v, w] : adj[u]) {
            if (fa[u] == v) continue;
            top[v] = v == adj[u][0][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};