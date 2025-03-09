template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    int size;
    int log;
    std::vector<Info> info;
    std::vector<Tag> tag;

    LazySegmentTree() :LazySegmentTree(0) {}
    explicit LazySegmentTree(int n) : LazySegmentTree(std::vector(n, Info())) {}
    explicit LazySegmentTree(const std::vector<Info>& v) : n(v.size()) {
        size = std::__bit_ceil(n);
        log = std::__countr_zero(size);
        info.assign(size, Info());
        info.insert(info.end(), v.begin(), v.end());
        info.resize(2 * size, Info());
        tag.assign(size, Tag());

        for (int i = size - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void modify(int p, const Info& v) {
        p += size;
        for (int i = log; i >= 1; i--) {
            push(p >> i);
        }
        info[p] = v;
        for (int i = 1; i <= log; i++) {
            pull(p >> i);
        }
    }

    constexpr Info operator[](int p) {
        p += size;
        for (int i = log; i >= 1; i--) {
            push(p >> i);
        }
        return info[p];
    }

    constexpr Info operator()(int l, int r) {
        if (l == r) {
            return Info();
        }

        Info a = Info(), b = Info();
        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if ((l >> i << i) != l) {
                push(l >> i);
            }
            if ((r >> i << i) != r) {
                push((r - 1) >> i);
            }
        }

        while (l < r) {
            if (l & 1) {
                a = a + info[l++];
            }
            if (r & 1) {
                b = info[--r] + b;
            }
            l >>= 1;
            r >>= 1;
        }
        return a + b;
    }

    void rangeApply(int l, int r, const Tag& t) {
        if (l == r) {
            return;
        }
        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if ((l >> i << i) != l) {
                push(l >> i);
            }
            if ((r >> i << i) != r) {
                push((r - 1) >> i);
            }
        }

        for (int x = l, y = r; x < y; x >>= 1, y >>= 1) {
            if (x & 1) {
                apply(x++, t);
            }
            if (y & 1) {
                apply(--y, t);
            }
        }

        for (int i = 1; i <= log; i++) {
            if ((l >> i << i) != l) {
                pull(l >> i);
            }
            if ((r >> i << i) != r) {
                pull((r - 1) >> i);
            }
        }
    }

    int maxRight(int l, auto&& pred) {
        if (l == n) {
            return n;
        }

        l += size;
        for (int i = log; i >= 1; i--) {
            push(l >> i);
        }

        Info cur = Info();

        do {
            while (l % 2 == 0) {
                l >>= 1;
            }
            if (!pred(cur + info[l])) {
                while (l < size) {
                    push(l);
                    l <<= 1;
                    if (pred(cur + info[l])) {
                        cur = cur + info[l++];
                    }
                }
                return l - size;
            }
            cur = cur + info[l++];
        } while ((l & -l) != l);
        return n;
    }

    int minLeft(int r, auto&& pred) {
        if (r == 0) {
            return 0;
        }

        r += size;
        for (int i = log; i >= 1; i--) {
            push((r - 1) >> i);
        }

        Info cur = Info();

        do {
            r--;
            while (r > 1 && (r & 1)) {
                r >>= 1;
            }
            if (!pred(info[r] + cur)) {
                while (r < size) {
                    push(r);
                    r = r << 1 | 1;
                    if (pred(info[r] + cur)) {
                        cur = info[r--] + cur;
                    }
                }
                return r + 1 - size;
            }
            cur = info[r] + cur;
        } while ((r & -r) != r);
        return 0;
    }

    void apply(int p, const Tag& t) {
        info[p].apply(t);
        if (p < size) {
            tag[p].apply(t);
        }
    }

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void push(int p) {
        apply(p << 1, tag[p]);
        apply(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }
};

struct Tag {
    void apply(const Tag& t) {}
};

struct Info {
    void apply(const Tag& t) {}
    constexpr friend Info operator+(const Info& a, const Info& b) {
        Info res{};
        res = {};
        return res;
    }
};