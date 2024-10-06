struct Trie : std::vector<std::array<int, 2>> {
    Trie(int n = 0) { this->reserve(n + 1); newNode(); }

    int newNode() {
        this->push_back({});
        return this->size() - 1;
    }

    template<class T>
    void add(T x) {
        int p = 0;
        int hi = std::numeric_limits<T>::digits - 1;

        for (int i = hi; i >= 0; i--) {
            int d = x >> i & 1;
            if (!(*this)[p][d]) {
                (*this)[p][d] = newNode();
            }
            p = (*this)[p][d];
        }
    }

    template<class T>
    int query(T x) {
        int p = 0;
        T ans = 0;
        int hi = std::numeric_limits<T>::digits - 1;

        for (int i = hi; i >= 0; i--) {
            int d = x >> i & 1;
            if ((*this)[p][!d]) {
                ans |= 1LL << i;
                p = (*this)[p][!d];
            } else {
                p = (*this)[p][d];
            }
        }
        return ans;
    }
};