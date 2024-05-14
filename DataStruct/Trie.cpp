class Trie {
protected:
    constexpr static int A = 26;
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

    void add(std::string_view s) {
        int p = 1;
        for (auto c : s) {
            int d = c - 'a';
            if (t[p][d] == 0) {
                t[p][d] = newNode();
            }
            p = t[p][d];
            t[p].siz++;
        }
        t[p].cnt++;
    }
    int query(std::string_view s, char offset = 'a') {
        int p = 1;
        for (auto c : s) {
            int d = c - offset;
            p = t[p][d];
            if (p == 0) {
                return 0;
            }
        }
        return t[p].cnt;
    }
    template<class T> constexpr void operator+=(T& x) {
        add(x);
    }
    template<class T> constexpr auto operator()(T& x) {
        return query(x);
    }
};