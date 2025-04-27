struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : len{ 0 }, link{ 0 }, next{} {}
        constexpr int& operator[](int x) {
            return next[x];
        }
    };

    std::vector<Node> trie;

    AhoCorasick() {
        init();
    }

    void init() {
        trie.assign(2, Node());
        trie[0].next.fill(1);
        trie[0].len = -1;
    }

    int newNode() {
        trie.emplace_back();
        return trie.size() - 1;
    }

    int add(const std::vector<int>& a) {
        int p = 1;
        for (auto x : a) {
            if (trie[p].next[x] == 0) {
                trie[p].next[x] = newNode();
                trie[trie[p].next[x]].len = trie[p].len + 1;
            }
            p = trie[p].next[x];
        }
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
        std::vector<int> q;
        q.push_back(1);

        for (int _ = 0; _ < q.size(); _++) {
            int x = q[_];

            for (int i = 0; i < ALPHABET; i++) {
                if (trie[x].next[i] == 0) {
                    trie[x].next[i] = trie[trie[x].link].next[i];
                } else {
                    trie[trie[x].next[i]].link = trie[trie[x].link].next[i];
                    q.push_back(trie[x].next[i]);
                }
            }
        }

        return q;
    }

    int next(int p, int x) {
        return trie[p].next[x];
    }

    int next(int p, char c, char offset = 'a') {
        return next(p, c - offset);
    }

    int link(int p) {
        return trie[p].link;
    }

    int len(int p) {
        return trie[p].len;
    }

    int size() {
        return trie.size();
    }
};