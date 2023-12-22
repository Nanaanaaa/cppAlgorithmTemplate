template<typename T>
class CostFlow {
private:
    const int n;
    static constexpr T inf = std::numeric_limits<T>::max();
    T flow, cost;

    std::vector<std::tuple<int, T, T>> e;
    std::vector<std::vector<int>> g;
    std::vector<T> d;
    std::vector<bool> vis;

    struct Edge {
        int from;
        int to;
        T cap;
        T cost;
        T flow;
    };
public:
    CostFlow(int n) : n(n), g(n), vis(n) {}

    constexpr void addEdge(int u, int v, T c, T w = 0) {
        g[u].push_back(e.size());
        e.emplace_back(v, c, w);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -w);
    }

    constexpr bool spfa(int s, int t) {
        d.assign(n, inf);
        d[t] = 0;
        vis.assign(n, false);
        vis[t] = true;
        std::deque<int> q;
        q.push_back(t);

        while (!q.empty()) {
            auto u = q.front();
            q.pop_front();
            vis[u] = false;
            for (int i : g[u]) {
                auto& [v, c, w] = e[i];
                auto& [_, rc, __] = e[i ^ 1];
                if (rc && d[v] > d[u] - w) {
                    d[v] = d[u] - w;
                    if (!vis[v]) {
                        vis[v] = true;
                        if (!q.empty() && d[v] < d[q.front()]) {
                            q.push_front(v);
                        }
                        else {
                            q.push_back(v);
                        }
                    }
                }
            }
        }
        return d[s] != inf;
    }

    constexpr T dfs(int u, int t, T f) {
        vis[u] = true;
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int i : g[u]) {
            auto& [v, c, w] = e[i];
            auto& [_, rc, __] = e[i ^ 1];
            if (!vis[v] && c && d[u] - w == d[v]) {
                auto a = dfs(v, t, std::min(r, c));
                if (a) {
                    cost += a * w;
                    c -= a;
                    rc += a;
                    r -= a;
                    if (!r) return f;
                }
            }
        }
        return f - r;
    }

    constexpr std::pair<T, T> costFlow(int s, int t) {
        flow = cost = 0;
        while (spfa(s, t)) {
            vis[t] = true;
            while (vis[t]) {
                vis.assign(n, false);
                flow += dfs(s, t, inf);
            }
        }
        return { flow , cost };
    }

    constexpr std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
