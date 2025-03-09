#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = long long;

template<typename Node>
struct PersistentSegTree {
    constexpr static int V = 1000000000;
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
        node.reserve(n + 1);
        for (int i = 0; i < n; i++) {
            append(node[i], init_[i], 1);
        }
    }

    Node* build(const std::vector<int>& a, auto l, auto r) {
        Node* p = &pool[idx++];
        if (r - l == 1) {
            // p->v = a[l];
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

    Node* update(Node* ver, auto x, auto v) {
        return update(ver, 0, V + 1, x, v);
    }

    Node* update(Node* p, auto l, auto r, auto x, auto v) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];
        p->sum += v;

        if (r - l == 1) {
            return p;
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            p->l = update(p->l, l, m, x, v);
        } else {
            p->r = update(p->r, m, r, x, v);
        }
        return p;
    }

    i64 query(Node* t1, Node* t2, auto l, auto r, auto x) {
        if (r - l == 1) {
            return (t2 ? t2->sum : 0) - (t1 ? t1->sum : 0);
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, x);
        }
        i64 s = (t2 && t2->l ? t2->l->sum : 0) - (t1 && t1->l ? t1->l->sum : 0);
        return query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, x) + s;
    }
    i64 query(int l, int r, int x) {
        return query(node[l], node[r], 0, V + 1, x);
    }
};

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    i64 sum = 0;

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

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    PersistentSegTree<Node> pseg(n);
    for (int i = 0; i < n; i++) {
        pseg.append(pseg.node[i], a[i], a[i]);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;

        i64 ans = 1;
        while (true) {
            auto t = pseg.query(l, r, ans);
            if (t < ans) {
                break;
            }
            ans = t + 1;
        }

        std::cout << ans << "\n";
    }

    return 0;
}