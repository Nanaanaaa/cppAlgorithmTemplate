template<int A = 26>
class Trie {
protected:
    struct Node {
        std::array<int, A> next{};
        int siz = 0;
        int cnt = 0;
        constexpr int& operator[](int x) {
            return next[x];
        }
    };
    std::vector<Node> t;
public:
    using i64 = int64_t;
    Trie() {
        init();
    }
    Trie(int __n) {
        t.reserve(__n);
        init();
    }
    ~Trie() {
        t.clear();
        t.shrink_to_fit();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int& siz(int p) {
        return t[p].siz;
    }
    int& cnt(int p) {
        return t[p].cnt;
    }
    void add(int& p, int d) {
        if (t[p][d] == 0) {
            t[p][d] = newNode();
        }
        p = t[p][d];
        t[p].siz++;
    }
    void add(int x) {
        int p = 1;
        for (int i = 30; ~i; i--) {
            bool d = x >> i & 1;
            add(p, d);
        }
        t[p].cnt++;
    }

    void add(i64 x) {
        int p = 1;
        for (int i = 62; ~i; i--) {
            bool d = x >> i & 1;
            add(p, d);
        }
        t[p].cnt++;
    }

    void add(const std::string_view& s) {
        int p = 1;
        for (auto c : s) {
            int d = c - 'a';
            add(p, d);
        }
        t[p].cnt++;
    }

    int query(int x) {
        int p = 1;
        int res = 0;
        for (int i = 30; ~i; i--) {
            bool d = x >> i & 1;
            if (t[p][!d]) {
                res |= 1 << i;
                p = t[p][!d];
            }
            else {
                p = t[p][d];
            }
        }
        return res;
    }

    i64 query(i64 x) {
        int p = 1;
        i64 res = 0;
        for (int i = 62; ~i; i--) {
            bool d = x >> i & 1;
            if (t[p][!d]) {
                res |= 1LL << i;
                p = t[p][!d];
            }
            else {
                p = t[p][d];
            }
        }
        return res;
    }

    int query(const std::string_view& s) {
        int p = 1;
        for (auto c : s) {
            int d = c - 'a';
            p = t[p][d];
            if (p == 0) {
                return 0;
            }
        }
        return t[p].cnt;
    }
    template<class T> constexpr void operator>>(T& x) {
        std::cin >> x;
        add(x);
    }
    template<class T> constexpr auto operator()(T& x) {
        return query(x);
    }
};