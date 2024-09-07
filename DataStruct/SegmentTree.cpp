int lg(unsigned int x) {
    return std::bit_width(x) - 1;
}

template <class Info>
struct SegmentTree {
    int n;
    std::vector<Info> tr;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    explicit SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        tr.assign(4 << lg(n), Info());
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

    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            tr[p] = v;
            return;
        }
        int m = std::midpoint(l, r);
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
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

    int findFirst(int p, int l, int r, int x, int y, auto&& pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(tr[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = std::midpoint(l, r);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    int findFirst(int x, int y, auto&& pred) {
        return findFirst(1, 0, n, x, y, pred);
    }

    int findLast(int p, int l, int r, int x, int y, auto&& pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(tr[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = std::midpoint(l, r);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    int findLast(int x, int y, auto&& pred) {
        return findLast(1, 0, n, x, y, pred);
    }

    struct Proxy {
        SegmentTree& seg{};
        int i = 0, j = 1;
        Info val{};
        Proxy(SegmentTree& seg, int i, int j) :seg(seg), i(i), j(j), val(seg.rangeQuery(i, j)) {}
        constexpr Info* operator->() {
            return &val;
        }
        constexpr Info operator*() {
            return val;
        }
        constexpr Proxy& operator=(const Info& info) {
            seg.modify(i, info);
            return *this;
        }
    };
    constexpr Proxy operator[](int i) {
        return Proxy(*this, i, i + 1);
    }
    constexpr Info operator()(int i, int j) {
        return rangeQuery(i, j);
    }
};