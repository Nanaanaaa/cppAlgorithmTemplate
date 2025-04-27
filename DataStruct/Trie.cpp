template<typename T = int>
struct Trie {
    constexpr static int hi = std::numeric_limits<T>::digits;

    struct Node {
        std::array<Node*, 2> ch;
        Node() : ch{} {}
    };

    Node* root;
    Node* pool;
    int tot;

    Trie(int n) {
        init(n);
    }
    ~Trie() {
        delete root;
        delete[] pool;
    }

    void init(int n) {
        tot = 0;
        root = new Node;
        pool = new Node[n * hi + 1];
    }

    void add(T x) {
        Node* p = root;
        for (int i = hi - 1; i >= 0; i--) {
            bool d = x >> i & 1;
            if (p->ch[d] == nullptr) {
                p->ch[d] = &pool[tot++];
            }
            p = p->ch[d];
        }
    }

    T query(T x) {
        Node* p = root;
        T ans = 0;
        for (int i = hi - 1; i >= 0; i--) {
            bool d = x >> i & 1;
            if (p->ch[d ^ 1] != nullptr) {
                ans |= T(1) << i;
                d ^= 1;
            }
            p = p->ch[d];
        }
        return ans;
    }
};