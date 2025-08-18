template <class Info>
struct SegmentTree {
    int n;
    int size;
    int log;
    std::vector<Info> info;

    SegmentTree() :SegmentTree(0) {}
    explicit SegmentTree(int n) : SegmentTree(std::vector(n, Info())) {}
    explicit SegmentTree(const std::vector<Info>& v) : n(v.size()) {
        size = std::__bit_ceil(n);
        log = std::__countr_zero(size);
        info.assign(size, Info());
        info.insert(info.end(), v.begin(), v.end());
        info.resize(2 * size, Info());

        for (int i = size - 1; i >= 1; i--) {
            pull(i);
        }
    }

    void modify(int p, const Info& v) {
        p += size;
        info[p] = v;
        for (int i = 1; i <= log; i++) {
            pull(p >> i);
        }
    }

    constexpr Info operator[](int p) const {
        return info[p + size];
    }

    constexpr Info operator()(int l, int r) const {
        if (l == r) {
            return Info();
        }

        l += size;
        r += size;
        Info a = Info(), b = Info();

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

    template<typename F>
    int maxRight(int l, F&& pred) const {
        if (l == n) {
            return n;
        }

        l += size;
        Info cur = Info();

        do {
            while (l % 2 == 0) {
                l >>= 1;
            }
            if (!pred(cur + info[l])) {
                while (l < size) {
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

    template<typename F>
    int minLeft(int r, F&& pred) const {
        if (0 == r) {
            return 0;
        }

        r += size;
        Info cur = Info();

        do {
            r--;
            while (r > 1 && (r & 1)) {
                r >>= 1;
            }
            if (!pred(info[r] + cur)) {
                while (r < size) {
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

    void pull(int p) {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
};

struct Info {
    constexpr friend Info operator+(const Info& a, const Info& b) {
        Info res{};
        res = {};
        return res;
    }
};