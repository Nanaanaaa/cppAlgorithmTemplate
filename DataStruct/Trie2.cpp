constexpr int N = 1E5 * 30, A = 2;
template<int N = ::N, int A = ::A>
class Trie {
private:
    struct Node {
        int ch[A]{};
        int siz = 0;
        int cnt = 0;
        constexpr int& operator[](int x) {
            return ch[x];
        }
    };
    std::array<Node, N> tr{};
    int cur = -1;
    constexpr int newNode() {
        cur++;
        tr[cur] = {};
        return cur;
    }
public:
    using i64 = int64_t;
    constexpr void init() {
        cur = -1;
        newNode();
    }
    constexpr Trie() {
        cur = -1;
        init();
    }
    ~Trie() {
        cur = -1;
    }
    constexpr void add(const int& x) noexcept {
        int p = 0;
        for (int i = 30; ~i; i--) {
            bool d = x >> i & 1;
            if (tr[p][d] == 0) {
                tr[p][d] = newNode();
            }
            p = tr[p][d];
        }
    }

    constexpr void add(const i64& x) noexcept {
        int p = 0;
        for (int i = 62; ~i; i--) {
            bool d = x >> i & 1;
            if (tr[p][d] == 0) {
                tr[p][d] = newNode();
            }
            p = tr[p][d];
            tr[p].siz++;
        }
        tr[p].cnt++;
    }
    constexpr void add(const std::string& s) noexcept {
        int p = 0;
        for (const auto& c : s) {
            int d = c - 'a';
            if (tr[p][d] == 0) {
                tr[p][d] = newNode();
            }
            p = tr[p][d];
            tr[p].siz++;
        }
    }
    constexpr void add(const char* s) noexcept {
        int p = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            int d = s[i] - 'a';
            if (tr[p][d] == 0) {
                tr[p][d] = newNode();
            }
            p = tr[p][d];
            tr[p].siz++;
        }
    }

    constexpr int query(const int& x) noexcept {
        int p = 0;
        int res = 0;
        for (int i = 30; ~i; i--) {
            bool d = x >> i & 1;
            if (tr[p][!d]) {
                res |= 1 << i;
                p = tr[p][!d];
            }
            else {
                p = tr[p][d];
            }
        }
        return res;
    }
    constexpr i64 query(const i64& x) noexcept {
        int p = 0;
        i64 res = 0;
        for (int i = 62; ~i; i--) {
            bool d = x >> i & 1;
            if (tr[p][!d]) {
                res |= 1LL << i;
                p = tr[p][!d];
            }
            else {
                p = tr[p][d];
            }
        }
        return res;
    }
    constexpr int query(const std::string& s) noexcept {
        int p = 0;
        for (const auto& c : s) {
            int d = c - 'a';
            p = tr[p][d];
            if (p == 0) {
                return 0;
            }
        }
        return tr[p].siz;
    }
    constexpr int query(const char* s) noexcept {
        int p = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            int d = s[i] - 'a';
            p = tr[p][d];
            if (p == 0) {
                return 0;
            }
        }
        return tr[p].siz;
    }
};
Trie tr;