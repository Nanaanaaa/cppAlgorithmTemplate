template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> tr;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        tr.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        auto build = [&](auto&& self, int p, int l, int r) {
            if (r - l == 1) {
                tr[p] = init_[l];
                return;
            }
            int m = std::midpoint(l, r);
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }

    void pull(int p) {
        tr[p] = tr[2 * p] + tr[2 * p + 1];
    }

    void apply(int p, const Tag& t) {
        tr[p].apply(t);
        tag[p].apply(t);
    }

    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            tr[p] = v;
            return;
        }
        int m = std::midpoint(l, r);
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const Info& v) {
        modify(1, 0, n, x, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return tr[p];
        }
        int m = std::midpoint(l, r);
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag& t) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            return apply(p, t);
        }
        int m = std::midpoint(l, r);
        push(p);
        rangeApply(2 * p, l, m, x, y, t);
        rangeApply(2 * p + 1, m, r, x, y, t);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag& t) {
        return rangeApply(1, 0, n, l, r, t);
    }

    int findFirst(int p, int l, int r, int x, int y, auto&& pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = std::midpoint(l, r);
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    int findFirst(int l, int r, auto&& pred) {
        return findFirst(1, 0, n, l, r, pred);
    }

    int findLast(int p, int l, int r, int x, int y, auto&& pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = std::midpoint(l, r);
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    int findLast(int l, int r, auto&& pred) {
        return findLast(1, 0, n, l, r, pred);
    }

    struct Proxy {
        LazySegmentTree& seg;
        int i, j;
        Info val;
        Proxy(LazySegmentTree& seg, int i, int j) :seg(seg), i(i), j(j), val(seg.rangeQuery(i, j)) {}
        constexpr Info* operator->() {
            return &val;
        }
        constexpr Proxy& operator=(const Info& info) {
            assert(i + 1 == j);
            seg.modify(i, info);
            return *this;
        }
        constexpr Proxy& operator+=(const Tag& tag) {
            seg.rangeApply(i, j, tag);
            return *this;
        }
    };
    constexpr Proxy operator[](int i) {
        return Proxy(*this, i, i + 1);
    }
    constexpr Proxy operator()(int i, int j) {
        return Proxy(*this, i, j);
    }
};