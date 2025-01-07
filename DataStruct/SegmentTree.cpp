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

    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
};

struct Info {};
constexpr Info operator+(const Info& a, const Info& b) {
    Info res{};
    res = {};
    return res;
}