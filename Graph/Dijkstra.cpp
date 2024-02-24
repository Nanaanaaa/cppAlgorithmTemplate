// std::priority_queue
template<class T = int>
std::vector<T> dijkstra(int s, const auto& adj, T init_ = -1) {
    using e = std::pair<T, int>;
    const int n = adj.size();

    std::vector<T> dis(n, init_);
    std::priority_queue<e, std::vector<e>, std::greater<>> q;
    q.emplace(0, s);

    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (dis[u] != init_) continue;
        dis[u] = d;

        for (auto [v, w] : adj[u]) {
            q.emplace(d + w, v);
        }
    }
    return dis;
}