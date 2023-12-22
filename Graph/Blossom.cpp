struct Blossom {
    const int n;

    std::vector<std::pair<int, int>> e;
    std::vector<std::vector<int>> g;

    Blossom(int n) :n(n), g(n) {}

    int addEdge(int u, int v) {
        int id = e.size();
        g[u].push_back(id);
        g[v].push_back(id);
        e.emplace_back(u, v);
        return id;
    }

    std::vector<int> matching() {
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::vector<int> match(n, -1);// 匹配
        std::vector<int> dfn(n, -1);
        std::vector<int> label(n); // 「o」或「i」
        std::vector<int> orig(n); // 花根
        std::vector<int> fa(n, -1);
        std::queue<int> q;
        int cur = -1;

        auto lca = [&](int u, int v) {
            cur++;
            while (true) {
                if (u != -1) {
                    if (dfn[u] == cur) {  // 找到拜访过的点 也就是LCA
                        return u;
                    }
                    dfn[u] = cur;
                    if (match[u] == -1) {
                        u = -1;
                    }
                    else {
                        u = orig[fa[match[u]]];  // 以匹配点的父节点继续寻找
                    }
                }
                std::swap(u, v);
            }
        };  // lca

        auto blossom = [&](int u, int v, int a) {
            while (orig[u] != a) {
                fa[u] = v;
                v = match[u];
                if (label[v] == 1) {  // 初始点设为"o" 找增广路
                    label[v] = 0;
                    q.push(v);
                }
                orig[u] = orig[v] = a;  // 缩花
                u = fa[v];
            }
        };  // blossom

        auto augment = [&](int u) {
            while (u != -1) {
                int pv = fa[u];
                int next_v = match[pv];
                match[u] = pv;
                match[pv] = u;
                u = next_v;
            }
        };  // augment

        auto bfs = [&](int root) {
            std::fill(label.begin(), label.end(), -1);
            std::iota(orig.begin(), orig.end(), 0);
            q = std::queue<int>();

            q.push(root);
            // 初始点设为 "o", 这里以"0"代替"o", "1"代替"i"
            label[root] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int id : g[u]) {
                    auto [from, to] = e[id];
                    int v = from ^ to ^ u;
                    if (label[v] == -1) {  // 找到未拜访点
                        label[v] = 1;        // 标记 "i"
                        fa[v] = u;
                        if (match[v] == -1) {  // 找到未匹配点
                            augment(v);          // 寻找增广路径
                            return true;
                        }
                        // 找到已匹配点 将与她匹配的点丢入queue 延伸交错树
                        label[match[v]] = 0;
                        q.push(match[v]);
                        continue;
                    }
                    else if (label[v] == 0 && orig[u] != orig[v]) {
                        // 找到已拜访点 且标记同为"o" 代表找到"花"
                        int a = lca(orig[u], orig[v]);
                        // 找LCA 然后缩花
                        blossom(v, u, a);
                        blossom(u, v, a);
                    }
                }
            }
            return false;
        };  // bfs

        auto greedy = [&]() {
            std::vector<int> order(n);
            // 随机打乱 order
            std::iota(order.begin(), order.end(), 0);
            std::shuffle(order.begin(), order.end(), rng);

            // 将可以匹配的点匹配
            for (int i : order) {
                if (match[i] == -1) {
                    for (auto id : g[i]) {
                        auto [from, to] = e[id];
                        to ^= from ^ i;
                        if (match[to] == -1) {
                            match[i] = to;
                            match[to] = i;
                            break;
                        }
                    }
                }
            }
        };  // greedy

        // 一开始先随机匹配
        greedy();
        // 对未匹配点找增广路
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                bfs(i);
            }
        }
        return match;
    }
};