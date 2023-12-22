std::vector<double> y;

template <typename Info>
struct ScanLine {
    int n;
    std::vector<Info> tr;

    ScanLine(int n) :n(n), tr(4 << std::__lg(n)) {}

    void pull(int p, int l, int r) {
        if (tr[p].cnt) {
            tr[p].len = ::y[r] - ::y[l];
        }
        else if (r - l == 1) {
            tr[p].len = 0;
        }
        else {
            tr[p].len = tr[2 * p].len + tr[2 * p + 1].len;
        }
    }

    void rangeApply(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            tr[p].cnt += v;
        }
        else {
            int m = (l + r) / 2;
            rangeApply(2 * p, l, m, x, y, v);
            rangeApply(2 * p + 1, m, r, x, y, v);
        }
        pull(p, l, r);
    }

    void rangeApply(int l, int r, int v) {
        rangeApply(1, 0, n, l, r, v);
    }
};

template<typename T>
struct Info {
    int cnt;
    T len;
};

template<typename T>
struct Segment {
    T x, y1, y2;
    int k;
    bool operator < (const Segment& rhs) const {
        return x < rhs.x || x == rhs.x && k > rhs.k;
    }
};
