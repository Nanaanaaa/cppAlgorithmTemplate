#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = long long;

template<typename Node>
struct PersistentSegTree {
    constexpr static int V = 1000000;
    int n;
    std::vector<Node*> node;
    Node* pool;
    int idx;

    PersistentSegTree() {}
    PersistentSegTree(int n_) :n(n_), idx(0) {
        pool = static_cast<Node*>(std::calloc(2 * n * (std::__lg(V) + 1), sizeof(Node)));
        node.reserve(n + 1);
        node.emplace_back(&pool[idx++]);
    }
    template<typename T>
    PersistentSegTree(const std::vector<T>& init_) : n(init_.size()), idx(0) {
        pool = static_cast<Node*>(std::calloc(2 * n * (std::__lg(V) + 1), sizeof(Node)));
        node.resize(n + 1);
        for (int i = 0; i < n; i++) {
            node[i + 1] = add(node[i], 0, V + 1, init_[i]);
        }
    }

    Node* build(const std::vector<int>& a, auto l, auto r) {
        Node* p = &pool[idx++];
        if (r - l == 1) {
            p->v = a[l];
            return p;
        }
        auto m = std::midpoint(l, r);
        p->l = build(a, l, m);
        p->r = build(a, m, r);
        return p;
    }

    void add(auto x, auto v) {
        node.emplace_back(add(node.back(), 0, V + 1, x, v));
    }

    Node* add(Node* p, auto l, auto r, auto x, auto v) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];

        if (r - l == 1) {
            p->v = v;
            return p;
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            p->l = add(p->l, l, m, x, v);
        } else {
            p->r = add(p->r, m, r, x, v);
        }
        return p;
    }

    int query(Node* t, auto l, auto r, int x) {
        if (!t) {
            return 0;
        }
        if (r - l == 1) {
            return t->v;
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            return query(t->l, l, m, x);
        }
        return query(t->r, m, r, x);
    }
};

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    // int cnt = 0;
    int v = 0;
    Node() {}
    Node(Node* t) {
        if (t != nullptr) {
            *this = *t;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    PersistentSegTree<Node> pseg(m);
    pseg.node[0] = pseg.build(a, 0, n);

    for (int i = 1; i <= m; i++) {
        int ver, o, x, v;
        std::cin >> ver >> o >> x;
        x--;

        if (o == 1) {
            std::cin >> v;
            pseg.node[i] = pseg.add(pseg.node[ver], 0, n, x, v);
        } else {
            std::cout << pseg.query(pseg.node[ver], 0, n, x) << "\n";
            pseg.node[i] = pseg.node[ver];
        }
    }

    return 0;
}