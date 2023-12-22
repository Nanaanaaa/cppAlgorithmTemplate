class KMP {
protected:
    int n;
    std::string p;
public:
    std::vector<int> next;
    KMP(const std::string& pattern) { init(pattern); }
    ~KMP() {
        p.clear();
        p.shrink_to_fit();
        next.clear();
        next.shrink_to_fit();
    }
    void init() {
        for (int i = 1, j = -1; i < n; i++) {
            while (j != -1 && p[j + 1] != p[i]) {
                j = next[j];
            }
            if (p[j + 1] == p[i]) {
                j++;
            }
            next[i] = j;
        }
    }
    void init(const std::string& pattern) {
        p = std::move(pattern);
        n = p.size();
        next.assign(n, -1);
        init();
    }
    std::vector<int> work(const std::string& s) {
        const int m = s.size();
        std::vector<int> res;
        for (int i = 0, j = -1; i < m; i++) {
            while (j != -1 && p[j + 1] != s[i]) {
                j = next[j];
            }
            if (p[j + 1] == s[i]) {
                j++;
            }
            if (j == n - 1) {
                j = next[j];
                res.push_back(i - n + 1);
            }
        }
        return res;
    }
    bool empty() {
        return next.empty();
    }
    int front() {
        return next.front();
    }
    int back() {
        return next.back();
    }
};