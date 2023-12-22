// 来自 地道战 找连续的1中左右第一个0

int findFirst(int k) {
    int pre = preQuery(k + 1);
    if (pre == k + 1) return 0;
    int x = 0, sum = 0;
    for (int i = 1 << std::__lg(n); i; i /= 2) {
        if (x + i - 1 >= n) continue;
        if (x + i - 1 < k && pre - sum - a[x + i - 1] != k - (x + i - 1)) {
            x += i;
            sum += a[x - 1];
        }
    }
    return x + 1;
}

int findLast(int k) {
    int pre = preQuery(k + 1);
    int x = 0, sum = 0;
    for (int i = 1 << std::__lg(n); i; i /= 2) {
        if (x + i - 1 >= n) continue;
        if (x + i - 1 < k || sum + a[x + i - 1] - pre == (x + i - 1) - k) {
            x += i;
            sum += a[x - 1];
        }
    }
    return x;
}

// 来自 格子旅行 广州省赛
int findFirst(int k, std::vector<int>& A) {
    int pre = preQueryColor(k + 1, A);
    if (pre == k + 1) return 0;
    int x = 0, cnt = 0;

    for (int i = 1 << std::__lg(n); i; i /= 2) {
        int to = x + i, tmp = 0;
        if (to - 1 >= n) continue;
        for (int& c : A) {
            auto it = tr[to - 1].col.find(c);
            if (it != tr[to - 1].col.end()) {
                tmp += it->second;
            }
        }
        if (to - 1 < k && pre - cnt - tmp != k - (to - 1)) {
            x += i;
            cnt += tmp;
        }
    }
    return x + 1;
}

int findLast(int k, std::vector<int>& A) {
    int pre = preQueryColor(k + 1, A);
    int x = 0, cnt = 0;

    for (int i = 1 << std::__lg(n); i; i /= 2) {
        int to = x + i, tmp = 0;
        if (to - 1 >= n) continue;
        for (int& c : A) {
            auto it = tr[to - 1].col.find(c);
            if (it != tr[to - 1].col.end()) {
                tmp += it->second;
            }
        }
        if (to - 1 <= k || cnt + tmp - pre == to - 1 - k) {
            x = to;
            cnt += tmp;
        }
    }
    return x;
}