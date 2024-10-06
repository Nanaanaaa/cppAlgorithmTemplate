template<class K, class V>
struct ChthollyTree : std::map<K, V> {
    void split(int p) {
        this->emplace(p, std::prev(this->upper_bound(p))->second);
    }

    void rangeAssign(int l, int r, int v) {
        split(l);
        split(r);
        for (auto it = this->find(l); it->first < r; it = this->erase(it)) {}
        this->emplace(l, v);
    }

    void rangeAdd(int l, int r, int v) {
        split(l);
        split(r);
        for (auto it = this->find(l); it->first < r; it++) {
            it->second += v;
        }
    }
    i64 rangeKth(int l, int r, int k) {
        split(l);
        split(r);
        std::vector<std::pair<i64, int>> t;
        for (auto it = this->find(l); it->first < r; it++) {
            t.emplace_back(it->second, std::next(it)->first - it->first);
        }
        std::sort(t.begin(), t.end());
        for (auto [x, siz] : t) {
            k -= siz;
            if (k <= 0) {
                return x;
            }
        }
        return -1;
    }

    i64 rangeSum(int l, int r, int x, int y) {
        i64 ans = 0;
        split(l);
        split(r);
        for (auto it = this->find(l); it->first < r; it++) {
            ans += power(it->second, x, y) * (std::next(it)->first - it->first) % y;
            ans %= y;
        }
        return ans;
    }
};