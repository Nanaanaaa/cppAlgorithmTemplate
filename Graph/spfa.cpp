// 最短路
auto spfa = [&](int s) {
    std::queue<int> q;
    std::vector<int> vis(n);
    std::vector<int> dis(n, 1e9);

    q.push(s);
    vis[s] = true;
    dis[s] = 0;

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = false;

        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dis;
};

// 判断负环：queue/stack

auto spfa = [&]() {
    std::vector<int> dis(n, 1e9), vis(n, 1), cnt(n);
    std::vector<int> stk(n);
    std::iota(stk.begin(), stk.end(), 0);
    while (!stk.empty()) {
        auto u = stk.back();
        stk.pop_back();
        vis[u] = false;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) {
                    return true;
                }
                if (!vis[v]) {
                    stk.push_back(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
};
