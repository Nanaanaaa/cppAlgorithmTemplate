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

constexpr int M = 500;

struct HLD {
    int n;
    int cur;
    std::vector<int> siz, top, dep, fa, in, out;
    std::vector<int> seq; // 注意两倍空间
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
        seq.assign(2 * n, 0); // 注意
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
        seq[in[u]] = u; // 
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur++;
        seq[out[u]] = u; // 
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

struct Info {
    int l, r, p, id;
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    std::cin >> a;

    auto t = a;

    std::sort(t.begin(), t.end());
    t.erase(std::unique(t.begin(), t.end()), t.end());

    for (auto& x : a) {
        x = std::lower_bound(t.begin(), t.end(), x) - t.begin();
    }

    const int m = a.size();

    HLD hld(n);

    auto& in = hld.in;
    auto& out = hld.out;
    auto& seq = hld.seq;

    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        hld.addEdge(x, y);
    }

    hld.work();

    std::vector<Info> qry(q);
    for (int i = 0; i < q; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        if (in[x] > in[y]) {
            std::swap(x, y);
        }
        int p = hld.lca(x, y);
        if (x == p) {
            qry[i] = { in[x], in[y], -1, i };
        }
        else {
            qry[i] = { out[x], in[y], p, i };
        }
    }
    std::sort(qry.begin(), qry.end(), [&](const Info& a, const Info& b) {
        if (a.l / M != b.l / M) return a.l < b.l;
        return a.l / M % 2 ? a.r > b.r : a.r < b.r;
    });

    int l = 1, r = 0;
    std::vector<int> ans(q);
    int res = 0;

    std::vector<int> vis(n), cnt(n);

    auto add = [&](int i) {
        if (++cnt[a[i]] == 1) res++;
    };

    auto del = [&](int i) {
        if (--cnt[a[i]] == 0) res--;
    };

    auto modify = [&](int i) {
        vis[i] ? del(i) : add(i);
        vis[i] ^= 1;
    };

    for (auto [x, y, p, i] : qry) {
        while (l < x) modify(seq[l++]);
        while (l > x) modify(seq[--l]);
        while (r < y) modify(seq[++r]);
        while (r > y) modify(seq[r--]);
        if (~p) modify(p);
        ans[i] = res;
        if (~p) modify(p);
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}