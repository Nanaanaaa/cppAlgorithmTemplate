template<class Info>
struct Trie : std::vector<Info> {
    Trie(int n = 0) { this->reserve(n + 1); newNode(); }

    int newNode() {
        this->emplace_back();
        return this->size() - 1;
    }

    void add(std::string_view s) {
        int p = 0;
        for (auto c : s) {
            c -= 'a';
            if (!(*this)[p][c]) {
                (*this)[p][c] = newNode();
            }
            p = (*this)[p][c];
            this->at(p).siz++;
        }
        this->at(p).cnt++;
    }

    void add(const char* s) {
        add(std::string_view(s));
    }

    int query(std::string_view s) {
        int p = 0;
        for (auto c : s) {
            c -= 'a';
            p = (*this)[p][c];
            if (p == 0) {
                return 0;
            }
        }
        return this->at(p).cnt;
    }

    int query(const char* s) {
        return query(std::string_view(s));
    }
};

struct Info {
    constexpr static int ALPHABET_SIZE = 26;

    int cnt = 0;
    int siz = 0;
    std::array<int, ALPHABET_SIZE> tr{};

    constexpr int& operator[](int i) {
        return tr.at(i);
    }
};