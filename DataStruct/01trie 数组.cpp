constexpr int N = 30 * 2E5;
namespace T {
    int idx;
    int trie[N][2], cnt[N];

    int newNode() {
        ++idx;
        std::memset(trie[idx], 0, sizeof trie[idx]);
        cnt[idx] = 0;
        return idx;
    }

    void init() {
        idx = 0;
        newNode();
    }

    void add(int x) {
        int p = 1;
        for (int i = 30; ~i; i--) {
            bool d = x >> i & 1;
            if (!trie[p][d]) {
                trie[p][d] = newNode();
            }
            p = trie[p][d];
            cnt[p]++;
        }
    }
};
using namespace T;