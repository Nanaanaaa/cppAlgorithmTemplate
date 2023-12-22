template <int A = 26>
class AhoCorasick {
protected:
    struct Node {
        int len;
        int link;
        int cnt;
        std::array<int, A> next;
        Node() : len{}, link{}, cnt{}, next{} {}
        constexpr int& operator[](int x) {
            return next[x];
        }
    };
    std::vector<Node> t;
public:
    AhoCorasick() { init(); }
    ~AhoCorasick() {
        t.clear();
        t.shrink_to_fit();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const std::vector<int>& a) {
        int p = 1;
        for (auto x : a) {
            if (t[p][x] == 0) {
                t[p][x] = newNode();
                t[t[p][x]].len = t[p].len + 1;
            }
            p = t[p][x];
        }
        t[p].cnt++;
        return p;
    }

    int add(const std::string& a, char offset = 'a') {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return add(b);
    }

    std::vector<int> work() {
        std::vector<int> q{ 1 };
        for (int i = 0; i < q.size(); i++) {
            auto x = q[i];
            for (int i = 0; i < A; i++) {
                if (t[x][i] == 0) {
                    t[x][i] = t[t[x].link][i];
                }
                else {
                    t[t[x][i]].link = t[t[x].link][i];
                    q.push_back(t[x][i]);
                }
            }
        }
        return q;
    }

    int& next(int p, int x) {
        return t[p][x];
    }

    int& next(int p, char c, char offset = 'a') {
        return next(p, c - offset);
    }

    int& link(int p) {
        return t[p].link;
    }

    int& len(int p) {
        return t[p].len;
    }

    int& cnt(int p) {
        return t[p].cnt;
    }

    int size() {
        return t.size();
    }

    constexpr int& operator()(int p, auto x) {
        return next(p, x);
    }
    constexpr int& operator[](int p) {
        return t[p].link;
    }
    constexpr void operator+=(const std::string& s) {
        add(s);
    }
    constexpr void operator>>(std::string& s) {
        std::cin >> s;
        add(s);
    }
};