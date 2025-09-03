template<typename Node>
struct PersistentSegTree {
    using ptr = std::unique_ptr<Node>;

    constexpr static std::size_t V = 1000000000;
    int n;
    std::vector<ptr> node;  // Change to store unique_ptr instead of raw pointers.
    std::vector<ptr> pool;  // Pool to store nodes.
    int idx;

    // Default constructor
    PersistentSegTree() : n(0), idx(0) {}

    // Constructor with size
    PersistentSegTree(int n_) : n(n_), idx(0) {
        pool.reserve(2 * n * (std::__lg(V) + 1));  // Reserve memory upfront
        node.reserve(n + 1);
        node.push_back(nullptr);  // Reserve the root node.
    }

    // Constructor with initial values
    template<typename T>
    PersistentSegTree(const std::vector<T>& init_) : n(init_.size()), idx(0) {
        pool.reserve(2 * n * (std::__lg(V) + 1));  // Reserve memory upfront
        node.reserve(n + 1);
        node.push_back(nullptr);  // Reserve the root node.
        for (int i = 0; i < n; ++i) {
            append(node[0], i, init_[i]);
        }
    }

    // Build function
    ptr build(const std::vector<int>& a, std::size_t l, std::size_t r) {
        ptr p = std::make_unique<Node>();  // Create a new node.
        if (r - l == 1) {
            // p->v = a[l]; // Initialize leaf value if necessary
            return p;
        }
        auto m = std::midpoint(l, r);
        p->l = build(a, l, m);
        p->r = build(a, m, r);
        return p;
    }

    // Append function for adding a new version
    void append(std::size_t ver, std::size_t x, int v) {
        node.push_back(update(node[ver], x, v));
    }

    // Update function for creating new versions
    ptr update(std::size_t ver, std::size_t x, int v) {
        return update(node[ver], 0, V + 1, x, v);
    }

    // Update function for managing nodes
    ptr update(ptr p, std::size_t l, std::size_t r, std::size_t x, int v) {
        if (!p) {
            p = std::make_unique<Node>();
        }

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

    // Modify a specific version in the node array
    void modify(std::size_t x, ptr t) {
        node[x] = std::move(t);
    }

    // Query function to get the k-th element
    std::size_t query(ptr t1, ptr t2, std::size_t l, std::size_t r, int k) {
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

    // Public query function
    std::size_t query(std::size_t l, std::size_t r, int k) {
        return query(node[l], node[r], 0, V + 1, k);
    }
};
