Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= x && r <= y) {
        return tr[p];
    }
    if (y <= m) {
        return rangeQuery(2 * p, l, m, x, y);
    }
    else if (x >= m) {
        return rangeQuery(2 * p + 1, m, r, x, y);
    }
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
}

Info rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
}

// Lazy
Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= x && r <= y) {
        return tr[p];
    }
    push(p);
    if (y <= m) {
        return rangeQuery(2 * p, l, m, x, y);
    }
    else if (x >= m) {
        return rangeQuery(2 * p + 1, m, r, x, y);
    }
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
}

Info rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
}