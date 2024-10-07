#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int V = 1e9 + 10;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    i64 sum = 0;
    Node(Node* t) {
        if (t != nullptr) {
            *this = *t;
        }
    }
};

constexpr i64 lsum(const Node* t) {
    return t && t->l ? t->l->sum : 0;
}

constexpr i64 rsum(const Node* t) {
    return t && t->r ? t->r->sum : 0;
}

constexpr Node* rs(Node* t) {
    return t ? t->r : t;
}

constexpr Node* ls(Node* t) {
    return t ? t->l : t;
}

Node* add(Node* p, int l, int r, int x, int v) {
    p = new Node(p);
    p->sum += v;
    if (r - l == 1) {
        return p;
    }
    int m = (l + r) / 2;
    if (x < m) {
        p->l = add(p->l, l, m, x, v);
    }
    else {
        p->r = add(p->r, m, r, x, v);
    }
    return p;
}
Node* add(Node* p, int x, int v) {
    return add(p, 1, V, x, v);
}

i64 query(Node* t1, Node* t2, int l, int r, i64 x) {
    if (r - l == 1) {
        return (t2 ? t2->sum : 0) - (t1 ? t1->sum : 0);
    }
    int m = (l + r) / 2;
    i64 s = lsum(t2) - lsum(t1);
    if (x < m) {
        return query(ls(t1), ls(t2), l, m, x);
    }
    return query(rs(t1), rs(t2), m, r, x) + s;
}

i64 query(Node* t1, Node* t2, i64 x) {
    return query(t1, t2, 1, V, x);
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);

    for (auto& x : a) {
        std::cin >> x;
    }

    std::vector<Node*> node(n + 1);
    for (int i = 0; i < n; i++) {
        node[i + 1] = add(node[i], a[i], a[i]);
    }

    i64 ans = 0;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;
        ans = 1;
        while (true) {
            auto res = query(node[l], node[r], ans);
            if (res < ans) {
                break;
            }
            else {
                ans = res + 1;
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}