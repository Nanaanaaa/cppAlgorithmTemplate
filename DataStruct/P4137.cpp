#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = long long;

template<typename Node>
struct PersistentSegTree {
    constexpr static int V = 200000;
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
            append(node[i], init_[i], 1);
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

    void append(Node* ver, auto x, auto v) {
        node.emplace_back(update(ver, x, v));
    }

    Node* update(Node* p, auto l, auto r, auto x, auto v) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];

        if (r - l == 1) {
            p->min = v;
            return p;
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            p->l = update(p->l, l, m, x, v);
        } else {
            p->r = update(p->r, m, r, x, v);
        }
        p->min = std::min(p->l ? p->l->min : -1, p->r ? p->r->min : -1);
        return p;
    }
    Node* update(Node* ver, auto x, auto v) {
        return update(ver, 0, V + 1, x, v);
    }

    int query(Node* t, auto l, auto r, int x) {
        if (r - l == 1) {
            return l;
        }
        auto m = std::midpoint(l, r);
        if ((t && t->l ? t->l->min : -1) <= x) {
            return query(t ? t->l : nullptr, l, m, x);
        }
        return query(t ? t->r : nullptr, m, r, x);
    }
    int query(Node* t, int x) {
        return query(t, 0, V + 1, x);
    }
};

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int min = -1;

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
        a[i] = std::min(a[i], n);
    }

    PersistentSegTree<Node> pseg(n);
    for (int i = 0; i < n; i++) {
        pseg.append(pseg.node[i], a[i], i + 1);
    }

    while (m--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        std::cout << pseg.query(pseg.node[r], l) << "\n";
    }

    return 0;
}