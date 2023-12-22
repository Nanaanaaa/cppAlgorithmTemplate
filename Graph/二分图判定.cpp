auto judge = [&]() {
    std::queue<int> q;
    std::vector<int> col(n, -1);
    for (int i = 0; i < n; i++) {
        if (col[i] != -1) continue;
        q.push(i);
        col[i] = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (const auto& v : adj[u]) {
                if (col[v] == -1) {
                    q.push(v);
                    col[v] = col[u] ^ 1;
                }
                else if (col[v] == col[u]) {
                    return false;
                }
            }
        }
    }
    return true;
};

auto judge = [&]() {
    std::vector<int> col(n, -1);
    auto dfs = [&](auto dfs, int u, int c = 0) ->bool {
        col[u] = c;
        for (const auto& v : adj[u]) {
            if (col[v] == c || col[v] == -1 && !dfs(dfs, v, c ^ 1)) {
                return false;
            }
        }
        return true;
    };
    for (int i = 0; i < n; i++) {
        if (col[i] == -1 && !dfs(dfs, i, 0)) {
            return false;
        }
    }
    return true;
};