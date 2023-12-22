struct Node {
    int l, r;
    mutable i64 v;
    Node(const int& l, const int& r = 0, const i64& v = 0) :l(l), r(r), v(v) {}
    constexpr bool operator<(const Node& t) { return l < t.l; }
};

template <class Node>
struct ChthollyTree {
    std::set<Node> S;

    ChthollyTree(std::vector<int> w) {
        for (int i = 0; i < w.size(); i++) {
            S.emplace(i, i, w[i]);
        }
    }

    void insert(const Node& t) {
        S.emplace(t);
    }

    auto split(int pos) {
        auto it = S.lower_bound(Node(pos));
        if (it != S.end() && it->l == pos) {
            return it;
        }
        --it;
        int l = it->l, r = it->r;
        i64 v = it->v;
        S.erase(it);
        S.emplace(l, pos - 1, v);
        return S.emplace(pos, r, v).first;
    }

    void rangeAssign(int l, int r, int v) {
        auto it2 = split(r + 1), it1 = split(l);
        S.erase(it1, it2);
        S.emplace(l, r, v);
    }

    void rangeAdd(int l, int r, int v) {
        auto it2 = split(r + 1), it1 = split(l);
        for (auto it = it1; it != it2; ++it) {
            it->v += v;
        }
    }
};