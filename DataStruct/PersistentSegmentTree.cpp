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
        node.emplace_back(&pool[idx++]);
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

    void append(int ver, auto x, auto v) {
        node.emplace_back(update(ver, x, v));
    }
    void append(Node* ver, auto x, auto v) {
        node.emplace_back(update(ver, x, v));
    }

    Node* update(int ver, auto x, auto v) {
        return update(node[ver], 0, V + 1, x, v);
    }
    Node* update(Node* ver, auto x, auto v) {
        return update(ver, 0, V + 1, x, v);
    }

    Node* update(Node* p, auto l, auto r, auto x, auto v) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];
        p->cnt += v;

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

    void modify(int x, Node* t) {
        node[x] = t;
    }

    int query(Node* t1, Node* t2, auto l, auto r, int k) {
        if (r - l == 1) {
            return l;
        }
        int c = (t2 && t2->l ? t2->l->cnt : 0) - (t1 && t1->l ? t1->l->cnt : 0);
        auto m = std::midpoint(l, r);
        if (k <= c) {
            return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, k);
        }
        return query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, k - c);
    }
    int query(int l, int r, int k) {
        return query(node[l], node[r], 0, V + 1, k);
    }
};