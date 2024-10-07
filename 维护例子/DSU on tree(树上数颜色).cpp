#include <bits/stdc++.h>

template<typename P, typename Q> constexpr std::istream& operator>>(std::istream& is, std::pair<P, Q>& v) { std::cin >> v.first >> v.second; return is; }
template<typename P, typename Q> constexpr std::ostream& operator<<(std::ostream& os, std::pair<P, Q>& v) { std::cout << v.first << ' ' << v.second; return os; }
template<typename T, std::size_t N> constexpr std::istream& operator>>(std::istream& is, std::array<T, N>& v) { for (auto& i : v) is >> i; return is; }
template<typename T, std::size_t N> constexpr std::ostream& operator<<(std::ostream& os, std::array<T, N>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename T> constexpr std::istream& operator>>(std::istream& is, std::vector<T>& v) { for (auto& i : v) is >> i; return is; }
template<typename T> constexpr std::ostream& operator<<(std::ostream& os, std::vector<T>& v) { for (auto& i : v) os << i << ' '; return os; }
template<typename...Args> constexpr void debug(Args...args) { ((std::cerr << args << ' '), ...); std::cerr << '\n'; }
template<typename...Args> constexpr void println(Args...args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }
template<typename P, typename Q> constexpr void chmax(P& a, Q b) { a = (b > a ? b : a); }
template<typename P, typename Q> constexpr void chmin(P& a, Q b) { a = (b < a ? b : a); }

using i64 = int64_t;

struct HLD {
    int n;
    int cur;
    std::vector<int> siz, top, dep, fa, in, out;
    std::vector<int> seq;
    std::vector<std::vector<int>> adj;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.assign(n, 0);
        top.assign(n, 0);
        dep.assign(n, 0);
        fa.assign(n, 0);
        in.assign(n, 0);
        out.assign(n, 0);
        seq.assign(n, 0);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        fa[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (fa[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), fa[u]));
        }
        siz[u] = 1;
        for (auto& v : adj[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            }
            else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = fa[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    HLD hld(n);

    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        hld.addEdge(x, y);
    }

    hld.work();

    int res = 0;
    std::vector<int> col(n), ans(n), cnt(n + 1);
    std::cin >> col;

    auto add = [&](int u) {
        if (++cnt[col[u]] == 1) {
            res++;
        }
    };

    auto del = [&](int u) {
        if (--cnt[col[u]] == 0) {
            res--;
        }
    };

    auto dfs = [&](auto dfs, int u, int p, bool keep) ->void {
        for (auto v : hld.adj[u]) {
            if (v != p && v != hld.adj[u].front()) {
                dfs(dfs, v, u, false);
            }
        }
        if (hld.adj[u].front() != p) {
            dfs(dfs, hld.adj[u].front(), u, true);
        }
        for (auto v : hld.adj[u]) {
            if (v != p && v != hld.adj[u].front()) {
                for (int i = hld.in[v]; i < hld.out[v]; i++) {
                    add(hld.seq[i]);
                }
            }
        }
        add(u);
        ans[u] = res;
        if (!keep) {
            for (int i = hld.in[u]; i < hld.out[u]; i++) {
                del(hld.seq[i]);
            }
        }
    };

    dfs(dfs, 0, -1, false);

    int m;
    std::cin >> m;
    while (m--) {
        int p;
        std::cin >> p;
        std::cout << ans[p - 1] << "\n";
    }

    return 0;
}