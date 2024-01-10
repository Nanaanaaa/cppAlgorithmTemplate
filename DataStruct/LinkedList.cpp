struct LinkedList {
    int n;
    std::vector<int> pre, nxt;
    LinkedList(int n_) :n(n_), pre(n), nxt(n) {
        for (int i = 0; i < n; i++) {
            pre[i] = i - 1;
            nxt[i] = i + 1;
            if (nxt[i] == n) {
                nxt[i] = -1;
            }
        }
    }
    void erase(int i) {
        assert(i >= 0 && i < n);
        int l = pre[i], r = nxt[i];
        if (l == -1 && r == -1) {
            return;
        }
        nxt[i] = -1;
        pre[i] = -1;
        if (l != -1) {
            nxt[l] = r;
        }
        if (r != -1) {
            pre[r] = l;
        }
    }
    int prev(int i) {
        return pre[i];
    }
    int next(int i) {
        return nxt[i];
    }
};