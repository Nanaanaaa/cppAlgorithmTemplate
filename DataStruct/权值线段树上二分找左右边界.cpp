// 基本都是找第一个不符合check的位置 具体边界可以讨论

void modifyCol(int p, int l, int r, int x, const int& v, int t) {
    tr[p].map[v] += t;
    if (tr[p].map[v] == 0) {
        tr[p].map.erase(v);
    }
    if (r - l == 1) {
        return;
    }
    if (x < m) {
        modifyCol(2 * p, l, m, x, v, t);
    }
    else {
        modifyCol(2 * p + 1, m, r, x, v, t);
    }
}
void modifyCol(int x, const int& v, int t) {
    modifyCol(1, 0, n, x, v, t);
}

bool check(umap& map, const std::vector<int>& a, int v) {
    int res = 0;
    for (const int& x : a) {
        if (map.find(x) != map.end()) {
            res += map[x];
        }
    }
    return res == v;
}

int findLeft(int p, int l, int r, int x, const std::vector<int>& a) {
    if (check(tr[p].map, a, r - l)) {
        return -1;
    }
    if (r - l == 1) {
        return l + 1;
    }
    if (x < m) {
        return findLeft(2 * p, l, m, x, a);
    }
    int ret = findLeft(2 * p + 1, m, r, x, a);
    if (ret != -1) {
        return ret;
    }
    return findLeft(2 * p, l, m, x, a);
}

int findRight(int p, int l, int r, int x, const std::vector<int>& a) {
    if (check(tr[p].map, a, r - l)) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    if (x >= m) {
        return findRight(2 * p + 1, m, r, x, a);
    }
    int ret = findRight(2 * p, l, m, x, a);
    if (ret != -1) {
        return ret;
    }
    return findRight(2 * p + 1, m, r, x, a);
}

int findLeft(int x, const std::vector<int>& a) {
    return findLeft(1, 0, n, x, a);
}
int findRight(int x, const std::vector<int>& a) {
    return findRight(1, 0, n, x, a);
}
//--------------------------------------------------------------------------------
int findFirstUpper(int p, int l, int r, int x, int v) { // 向右找第一个不小于v的值
    if (tr[p].mx < v) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    if (x >= m) {
        return findFirstUpper(2 * p + 1, m, r, x, v);
    }
    int ret = findFirstUpper(2 * p, l, m, x, v);
    if (ret != -1) {
        return ret;
    }
    return findFirstUpper(2 * p + 1, m, r, x, v);
}

int findFirstLower(int p, int l, int r, int x, int v) { //向左找第一个不大于v的值
    if (tr[p].mn > v) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    if (x < m) {
        return findFirstLower(2 * p, l, m, x, v);
    }
    int ret = findFirstLower(2 * p + 1, m, r, x, v);
    if (ret != -1) {
        return ret;
    }
    return  findFirstLower(2 * p, l, m, x, v);
}

int findFirstUpper(int x, int v) {
    return findFirstUpper(1, 0, n, x, v);
}
int findFirstLower(int x, int v) {
    return findFirstLower(1, 0, n, x, v);
}

//----------------------------------------------------------------
bool check(const Info& p, int v) {
    return p == v;
}

int findLeft(int p, int l, int r, int x) {
    if (check(tr[p], r - l)) {
        return -1;
    }
    if (r - l == 1) {
        return l + 1;
    }
    if (x < m) {
        return findLeft(2 * p, l, m, x);
    }
    int res = findLeft(2 * p + 1, m, r, x);
    if (res != -1) {
        return res;
    }
    return findLeft(2 * p, l, m, x);
}

int findRight(int p, int l, int r, int x) {
    if (check(tr[p], r - l)) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    if (x >= m) {
        return findRight(2 * p + 1, m, r, x);
    }
    int res = findRight(2 * p, l, m, x);
    if (res != -1) {
        return res;
    }
    return findRight(2 * p + 1, m, r, x);
}

int findLeft(int x) {
    return findLeft(1, 0, n, x);
}
int findRight(int x) {
    return findRight(1, 0, n, x);
}
