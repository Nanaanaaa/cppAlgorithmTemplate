std::vector<int> match(n, -1);
std::vector<int> vis(n);
auto find = [&](auto find, int u) -> bool {
    for (auto v : g[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || find(find, match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
};
int res = 0;
for (int i = 0; i < n1; i++) {
    vis.assign(n, 0);
    if (find(find, i)) res++;
}