auto spfa = [&](const auto& adj) {
    std::vector<i64> dis(n);
    std::vector<int> vis(n, 1), cnt(n);
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        q.push(i);
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;

        for (auto [v, w] : adj[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] == n) return true;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
};