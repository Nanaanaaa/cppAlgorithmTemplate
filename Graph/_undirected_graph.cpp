// 不带权
std::vector<std::vector<int>> g(n);
auto addEdge = [&](int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
};

// 带权
std::vector<std::vector<std::array<int, 2>>> g(n);
auto addEdge = [&](int u, int v, int w) {
    g[u].push_back({ v, w });
    g[v].push_back({ u, w });
}