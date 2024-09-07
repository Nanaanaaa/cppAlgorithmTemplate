auto bfs = [&](int s, auto&& adj) {
    std::vector<int> dis(n, -1);
    std::queue<int> q;

    q.push(s);
    dis[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dis[v] != -1) {
                continue;
            }
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }

    return dis;
};