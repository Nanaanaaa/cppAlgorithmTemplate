int findFirst(int p, int l, int r, int x, int y, auto check) {
    if (l >= y || r <= x || !check(tr[p])) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    push(p);
    int res = findFirst(2 * p, l, m, x, y, check);
    if (res == -1) {
        res = findFirst(2 * p + 1, m, r, x, y, check);
    }
    return res;
}
int findFirst(int x, int y, auto check) {
    return findFirst(1, 0, n, x, y, check);
}

int findLast(int p, int l, int r, int x, int y, auto check) {
    if (l >= y || r <= x || !check(tr[p])) {
        return -1;
    }
    if (r - l == 1) {
        return l;
    }
    push(p);
    int res = findLast(2 * p + 1, m, r, x, y, check);
    if (res == -1) {
        res = findLast(2 * p, l, m, x, y, check);
    }
    return res;
}
int findLast(int x, int y, auto check) {
    return findLast(1, 0, n, x, y, check);
}