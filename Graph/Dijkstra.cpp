// std::priority_queue
template<class T = int>
std::vector<T> dijkstra(int s, const auto& adj, T init_ = -1) {
    using e = std::pair<T, int>;
    const int n = adj.size();

    std::vector<T> dis(n, init_);
    std::priority_queue<e, std::vector<e>, std::greater<>> S;
    S.emplace(0, s);

    while (!S.empty()) {
        auto [d, u] = S.top();
        S.pop();

        if (dis[u] != init_) continue;
        dis[u] = d;

        for (auto [v, w] : adj[u]) {
            S.emplace(d + w, v);
        }
    }
    return dis;
}