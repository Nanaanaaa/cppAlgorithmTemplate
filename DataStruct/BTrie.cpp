template<class Info>
struct BTrie : std::vector<Info> {
    BTrie(int n = 0) { this->reserve(n + 1); newNode(); }

    int newNode() {
        this->emplace_back();
        return this->size() - 1;
    }

    template<typename T>
    void add(const T& __x) {
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

    template<typename T>
    T query(const T& __x) {
        int p = 0;
        T ans = 0;
        int hi = std::numeric_limits<T>::digits - 1;

        for (int i = hi; i >= 0; i--) {
            int d = x >> i & 1;
            if ((*this)[p][!d]) {
                ans |= T(1) << i;
                p = (*this)[p][!d];
            } else {
                p = (*this)[p][d];
            }
        }
        return ans;
    }
};

struct Info {
    std::array<int, 2> tr{};
    constexpr int& operator[](int i) {
        return tr.at(i);
    }
};
