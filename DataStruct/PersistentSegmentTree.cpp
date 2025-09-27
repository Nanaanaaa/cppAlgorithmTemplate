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

    Node* build(const std::vector<int>& a, int l, int r) {
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

    void append(Node* ver, int x, int v) {
        node.emplace_back(update(ver, x, v));
    }

    Node* update(Node* ver, int x, int v) {
        return update(ver, 0, V + 1, x, v);
    }

    Node* update(Node* p, int l, int r, int x, int v) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];
        p->cnt += v;

        if (r - l == 1) {
            return p;
        }

        int m = std::midpoint(l, r);
        if (x < m) {
            p->l = update(p->l, l, m, x, v);
        } else {
            p->r = update(p->r, m, r, x, v);
        }
        return p;
    }

    int query(Node* t1, Node* t2, int l, int r, int k) {
        if (r - l == 1) {
            return l;
        }
        int lcnt = (t2 && t2->l ? t2->l->cnt : 0) - (t1 && t1->l ? t1->l->cnt : 0);
        int m = std::midpoint(l, r);
        if (k <= lcnt) {
            return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, k);
        }
        return query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, k - lcnt);
    }

    int query(int l, int r, int k) {
        return query(node[l], node[r], 0, V + 1, k);
    }
};

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