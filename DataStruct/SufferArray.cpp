struct SuffixArray {
    const int n;
    std::vector<int> sa, rnk, height;
    SuffixArray(std::string_view s) :n(s.size()) {
        sa.resize(n);
        height.resize(n - 1);
        rnk.resize(n);
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(), [&](int a, int b) {return s[a] < s[b];});
        rnk[sa[0]] = 0;
        for (int i = 0; i < n - 1; i++) {
            rnk[sa[i + 1]] = rnk[sa[i]] + (s[sa[i + 1]] != s[sa[i]]);
        }
        int k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        for (; rnk[sa[n - 1]] < n - 1; k *= 2) {
            tmp.clear();
            for (int i = 0; i < k; i++) {
                tmp.push_back(n - k + i);
            }
            for (auto i : sa) {
                if (i >= k) {
                    tmp.push_back(i - k);
                }
            }
            std::fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) {
                cnt[rnk[i]]++;
            }
            for (int i = 0; i < n - 1; i++) {
                cnt[i + 1] += cnt[i];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[rnk[tmp[i]]]] = tmp[i];
            }
            std::swap(rnk, tmp);
            rnk[sa[0]] = 0;
            for (int i = 0; i < n - 1; i++) {
                auto t = (tmp[sa[i]] < tmp[sa[i + 1]] || sa[i] + k == n || tmp[sa[i] + k] < tmp[sa[i + 1] + k]);
                rnk[sa[i + 1]] = rnk[sa[i]] + t;
            }
        }

        for (int i = 0, j = 0; i < n; i++) {
            if (rnk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rnk[i] - 1] + j < n && s[i + j] == s[sa[rnk[i] - 1] + j]; j++);
                height[rnk[i] - 1] = j;
            }
        }
    }
    constexpr int operator[](int i) const {
        return sa[i];
    }
};
template<class T, class Cmp = std::less<T>>
struct RMQ {
    const Cmp cmp = Cmp();
    static constexpr unsigned B = 64;
    using u64 = unsigned long long;
    int n;
    std::vector<std::vector<T>> a;
    std::vector<T> pre, suf, ini;
    std::vector<u64> stk;
    RMQ() {}
    RMQ(const std::vector<T>& v) {
        init(v);
    }
    void init(const std::vector<T>& v) {
        n = v.size();
        pre = suf = ini = v;
        stk.resize(n);
        if (!n) {
            return;
        }
        const int M = (n - 1) / B + 1;
        const int lg = std::__lg(M);
        a.assign(lg + 1, std::vector<T>(M));
        for (int i = 0; i < M; i++) {
            a[0][i] = v[i * B];
            for (int j = 1; j < B && i * B + j < n; j++) {
                a[0][i] = std::min(a[0][i], v[i * B + j], cmp);
            }
        }
        for (int i = 1; i < n; i++) {
            if (i % B) {
                pre[i] = std::min(pre[i], pre[i - 1], cmp);
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % B != B - 1) {
                suf[i] = std::min(suf[i], suf[i + 1], cmp);
            }
        }
        for (int j = 0; j < lg; j++) {
            for (int i = 0; i + (2 << j) <= M; i++) {
                a[j + 1][i] = std::min(a[j][i], a[j][i + (1 << j)], cmp);
            }
        }
        for (int i = 0; i < M; i++) {
            const int l = i * B;
            const int r = std::min(1U * n, l + B);
            u64 s = 0;
            for (int j = l; j < r; j++) {
                while (s && cmp(v[j], v[std::__lg(s) + l])) {
                    s ^= 1ULL << std::__lg(s);
                }
                s |= 1ULL << (j - l);
                stk[j] = s;
            }
        }
    }
    T operator()(int l, int r) {
        if (l / B != (r - 1) / B) {
            T ans = std::min(suf[l], pre[r - 1], cmp);
            l = l / B + 1;
            r = r / B;
            if (l < r) {
                int k = std::__lg(r - l);
                ans = std::min({ ans, a[k][l], a[k][r - (1 << k)] }, cmp);
            }
            return ans;
        } else {
            int x = B * (l / B);
            return ini[std::countr_zero(stk[r - 1] >> (l - x)) + l];
        }
    }
};
