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

    void add(auto v) {
        node.emplace_back(add(node.back(), 0, V + 1, v));
    }

    Node* add(Node* p, auto l, auto r, auto x) {
        if (p != nullptr) {
            pool[idx] = *p;
        }
        p = &pool[idx++];
        p->cnt++;

        if (r - l == 1) {
            return p;
        }
        auto m = std::midpoint(l, r);
        if (x < m) {
            p->l = add(p->l, l, m, x);
        } else {
            p->r = add(p->r, m, r, x);
        }
        return p;
    }

    int query(Node* t1, Node* t2, auto l, auto r, int k) {
        if (r - l == 1) {
            return l;
        }
        int c = (t2 && t2->l ? t2->l->cnt : 0) - (t1 && t1->l ? t1->l->cnt : 0);
        auto m = std::midpoint(l, r);
        if (k > c) {
            return query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, k - c);
        }
        return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, k);
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
