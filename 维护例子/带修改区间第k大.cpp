#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int V = 1e9 + 1;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int cnt = 0;
    Node() {}
    Node(Node* t) {
        if (t != nullptr) {
            *this = *t;
        }
    }
};

constexpr int lcnt(const Node* t) {
    return t && t->l ? t->l->cnt : 0;
}

constexpr int rcnt(const Node* t) {
    return t && t->r ? t->r->cnt : 0;
}

constexpr Node* rs(Node* t) {
    return t ? t->r : t;
}

constexpr Node* ls(Node* t) {
    return t ? t->l : t;
}

void add(Node*& p, int l, int r, int x, int v) {
    p = new Node(p);
    p->cnt += v;
    if (r - l == 1) {
        return;
    }
    int m = (l + r) / 2;
    if (x < m) {
        add(p->l, l, m, x, v);
    }
    else {
        add(p->r, m, r, x, v);
    }
}

int kth(std::vector<Node*>& t1, std::vector<Node*>& t2, int l, int r, int k) {
    if (r - l == 1) {
        return l;
    }
    int cnt = 0;
    for (auto& t : t1) {
        cnt -= lcnt(t);
    }
    for (auto& t : t2) {
        cnt += lcnt(t);
    }
    int m = (l + r) / 2;
    if (k > cnt) {
        for (auto& t : t1) {
            t = rs(t);
        }
        for (auto& t : t2) {
            t = rs(t);
        }
        return kth(t1, t2, m, r, k - cnt);
    }
    for (auto& t : t1) {
        t = ls(t);
    }
    for (auto& t : t2) {
        t = ls(t);
    }
    return kth(t1, t2, l, m, k);
}

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> tr;
    Fenwick(int n = 0) {
        init(n);
    }

    int lowbit(int i) {
        return i & -i;
    }

    void init(int n) {
        this->n = n;
        tr.assign(n, T());
    }

    void add(int p, int x, int v) {
        for (int i = p; i < n; i += lowbit(i)) {
            ::add(tr[i], 0, V, x, v);
        }
    }

    int rangeQuery(int l, int r, int k) {
        std::vector<Node*> t1, t2;
        for (int i = r; i > 0; i -= lowbit(i)) {
            t2.push_back(tr[i]);
        }
        for (int i = l; i > 0; i -= lowbit(i)) {
            t1.push_back(tr[i]);
        }
        return kth(t1, t2, 0, V, k);
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    std::cin >> a;

    Fenwick<Node*> fen(n + 1);

    for (int i = 0; i < n; i++) {
        fen.add(i + 1, a[i], 1);
    }

    while (q--) {
        char o;
        std::cin >> o;
        if (o == 'C') {
            int x, v;
            std::cin >> x >> v;
            x--;
            fen.add(x + 1, a[x], -1);
            a[x] = v;
            fen.add(x + 1, a[x], 1);
        }
        else {
            int l, r, k;
            std::cin >> l >> r >> k;
            l--;
            std::cout << fen.rangeQuery(l, r, k) << "\n";
        }
    }

    return 0;
}