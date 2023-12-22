struct LCA {
    const int n, m = 30;
    std::vector<std::array<int, 31>> fa;
    std::vector<int> dep, parent;

    LCA(int n, std::vector<std::vector<int>> g, int root = 0) : n(n), dep(n), fa(n), parent(n) {
        auto dfs = [&](auto dfs, int u) ->void {
            if (u != root) {
                g[u].erase(std::find(g[u].begin(), g[u].end(), fa[u][0]));
            }

            for (auto v : g[u]) {
                dep[v] = dep[u] + 1;
                fa[v][0] = parent[v] = u;
                for (int i = 1; i <= m; i++) {
                    fa[v][i] = fa[fa[v][i - 1]][i - 1];
                }
                dfs(dfs, v);
            }
        };
        dfs(dfs, root);
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            std::swap(u, v);
        }

        for (int k = m; ~k; k--) {
            if (dep[fa[u][k]] >= dep[v]) {
                u = fa[u][k];
            }
        }
        if (u == v) {
            return u;
        }

        for (int k = m; ~k; k--) {
            if (fa[u][k] != fa[v][k]) {
                u = fa[u][k], v = fa[v][k];
            }
        }
        return fa[u][0];
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};
