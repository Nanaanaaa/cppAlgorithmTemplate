// 本质不同的边多 用priority_queue 否则std::set
template<class T = int>
auto dijkstra(int s, auto& adj) {
    using e = std::pair<T, int>;
    const int n = adj.size();

    std::vector<T> dis(n, -1);
    std::set<e> S;
    S.emplace(0, s);

    while (!S.empty()) {
        auto [d, u] = *S.begin();
        S.erase(S.begin());

        if (dis[u] != -1) continue;
        dis[u] = d;

        for (auto [v, w] : adj[u]) {
            S.emplace(d + w, v);
        }
    }
    return dis;
}

// std::priority_queue

template<class T = int>
auto dijkstra(int s, auto& adj) {
    using e = std::pair<T, int>;
    const int n = adj.size();

    std::vector<T> dis(n, -1);
    std::priority_queue<e, std::vector<e>, std::greater<>> S;
    S.emplace(0, s);

    while (!S.empty()) {
        auto [d, u] = S.top();
        S.pop();

        if (dis[u] != -1) continue;
        dis[u] = d;

        for (auto [v, w] : adj[u]) {
            S.emplace(d + w, v);
        }
    }
    return dis;
}

// 朴素 小常数
template<class T = int>
auto dijkstra(int s, auto& adj) {
    using e = std::pair<T, int>;
    const T inf = std::numeric_limits<T>::max();
    const int n = adj.size();

    std::vector<T> dis(n, inf);
    std::vector<bool> vis(n);
    std::set<e> S;

    S.emplace(0, s);
    dis[s] = 0;
    while (!S.empty()) {
        auto [d, u] = *S.begin();
        S.erase(S.begin());

        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, w] : adj[u]) {
            if (dis[v] > d + w) {
                dis[v] = d + w;
                S.emplace(d + w, v);
            }
        }
    }

    for (auto& x : dis) {
        if (x == inf) x = -1;
    }
    return dis;
}