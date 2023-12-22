auto [in, fa, dep, top, siz] = std::tuple(hld.in, hld.fa, hld.dep, hld.top, hld.siz);

auto updateTree = [&](int u, const Tag& t) {
    seg.rangeApply(in[u], in[u] + siz[u], t);
};

auto queryTree = [&](int u) {
    return seg.rangeQuery(in[u], in[u] + siz[u]);
};

auto updatePath = [&](int u, int v, const Tag& t) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            std::swap(u, v);
        }
        seg.rangeApply(in[top[u]], in[u] + 1, t);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) {
        std::swap(u, v);
    }
    seg.rangeApply(in[v], in[u] + 1, t);
};

auto queryPath = [&](int u, int v) {
    Info res{};
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            std::swap(u, v);
        }
        res = res + seg.rangeQuery(in[top[u]], in[u] + 1);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) {
        std::swap(u, v);
    }
    return res + seg.rangeQuery(in[v], in[u] + 1);
};