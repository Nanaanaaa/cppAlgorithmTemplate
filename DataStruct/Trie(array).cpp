template<class T = int>
struct Trie {
    constexpr static int hi = std::numeric_limits<T>::digits;

    struct Node {
        std::array<int, 2> next;
        constexpr int& operator[](int i) {
            return next.at(i);
        }
        Node() : next{} {}
    };

    std::vector<Node> trie;

    Trie(int n = 0) {
        init(n);
    }

    void init(int n = 0) {
        trie.reserve(n * hi + 2);
        trie.assign(2, Node());
        trie[0].next.fill(1);
    }

    int newNode() {
        trie.emplace_back();
        return trie.size() - 1;
    }

    void add(T value) {
        int o = 1;

        for (int i = hi - 1; i >= 0; i--) {
            int& p = trie[o][value >> i & 1];
            if (!p) {
                p = newNode();
            }
            o = p;
        }
    }

    T query(T value) {
        T ans = 0;
        int o = 1;

        for (int i = hi - 1; i >= 0; i--) {
            int d = value >> i & 1;
            if (trie[o][!d]) {
                ans |= T(1) << i;
                d ^= 1;
            }
            o = trie[o][d];
        }
        return ans;
    }
};