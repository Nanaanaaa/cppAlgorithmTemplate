std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> q;
q.emplace(0, 0);

std::vector<i64> dis(n, -1);
while (!q.empty()) {
    auto [d, x] = q.top();
    q.pop();

    if (dis[x] != -1) {
        continue;
    }
    dis[x] = d;
    for (auto [y, w] : adj[x]) {
        q.emplace(d + w, y);
    }
}