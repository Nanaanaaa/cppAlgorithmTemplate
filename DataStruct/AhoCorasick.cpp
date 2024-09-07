template <int A = 26>
class AhoCorasick {
protected:
    struct Node {
        int len;
        int link;
        std::array<int, A> next;
        Node() : len{}, link{}, next{} {}
        constexpr int& operator[](int x) {
            return next[x];
        }
    };
    std::vector<Node> t;
public:
    AhoCorasick() { 
        init();
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

    int add(std::span<int> a) {
        int p = 1;
        for (auto x : a) {
            if (t[p][x] == 0) {
                t[p][x] = newNode();
                t[t[p][x]].len = t[p].len + 1;
            }
            p = t[p][x];
        }
        return p;
    }

    int add(std::string_view a, char offset = 'a') {
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
            for (int j = 0; j < A; j++) {
                if (t[x][j] == 0) {
                    t[x][j] = t[t[x].link][j];
                } else {
                    t[t[x][j]].link = t[t[x].link][j];
                    q.push_back(t[x][j]);
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
};