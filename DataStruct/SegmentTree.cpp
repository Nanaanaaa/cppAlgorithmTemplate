template <class Info>
struct SegmentTree {
#define m (l + r) / 2
    int n;
    std::vector<Info> tr;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        tr.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                tr[p] = { init_[l] };
                return;
            }
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p) {
        tr[p] = tr[2 * p] + tr[2 * p + 1];
    }

    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            tr[p] = v;
            return;
        }
        if (x < m) {
            modify(2 * p, l, m, x, v);
        }
        else {
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
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }

    constexpr Info operator()(int l, int r) {
        return rangeQuery(l, r);
    }

    int findFirst(int p, int l, int r, int x, int y, auto check) {
        if (l >= y || r <= x || !check(tr[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int res = findFirst(2 * p, l, m, x, y, check);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, check);
        }
        return res;
    }
    int findFirst(int x, int y, auto check) {
        return findFirst(1, 0, n, x, y, check);
    }

    int findLast(int p, int l, int r, int x, int y, auto check) {
        if (l >= y || r <= x || !check(tr[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int res = findLast(2 * p + 1, m, r, x, y, check);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, check);
        }
        return res;
    }
    int findLast(int x, int y, auto check) {
        return findLast(1, 0, n, x, y, check);
    }
#undef m
};