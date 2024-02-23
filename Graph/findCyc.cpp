std::vector<int> vis(n, -1);

auto dfs = [&](auto dfs, int u) {
    vis[u] = 0;
    for (auto v : adj[u]) {
        if (vis[v] == 0) {
            return true;
        }
        else if (vis[v] == -1) {
            if (dfs(dfs, v)) {
                return true;
            }
        }
    }
    vis[u] = 1;
    return false;
};