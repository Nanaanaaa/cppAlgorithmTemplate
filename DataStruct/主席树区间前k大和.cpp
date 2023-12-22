constexpr int V = 1e9 + 1;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int cnt = 0;
    i64 sum = 0;
    Node(Node* t) {
        if (t != nullptr) {
            *this = *t;
        }
    }
};

constexpr int lcnt(const Node* t) {
    return t && t->l ? t->l->cnt : 0;
}

constexpr i64 lsum(const Node* t) {
    return t && t->l ? t->l->sum : 0;
}
constexpr i64 rsum(const Node* t) {
    return t && t->r ? t->r->sum : 0;
}

constexpr int rcnt(const Node* t) {
    return t && t->r ? t->r->cnt : 0;
}

constexpr Node* rs(Node* t) {
    return t ? t->r : t;
}

constexpr Node* ls(Node* t) {
    return t ? t->l : t;
}

Node* add(Node* p, int l, int r, int x, int v) {
    p = new Node(p);
    p->cnt += v;
    p->sum += x;
    if (r - l == 1) {
        return p;
    }
    int m = (l + r) / 2;
    if (x < m) {
        p->l = add(p->l, l, m, x, v);
    }
    else {
        p->r = add(p->r, m, r, x, v);
    }
    return p;
}

int kmin(Node* t1, Node* t2, int l, int r, int k) {
    if (r - l == 1) {
        return l;
    }
    int cnt = lcnt(t2) - lcnt(t1);
    int m = (l + r) / 2;
    if (k > cnt) {
        return kmin(rs(t1), rs(t2), m, r, k - cnt);
    }
    return kmin(ls(t1), ls(t2), l, m, k);
}

i64 ksum(Node* t1, Node* t2, int l, int r, int k, i64 s = 0) {
    if (r - l == 1) {
        return s + 1LL * k * l;
    }
    int cnt = rcnt(t2) - rcnt(t1);
    i64 sum = rsum(t2) - rsum(t1);
    int m = (l + r) / 2;
    if (cnt > k) {
        return ksum(rs(t1), rs(t2), m, r, k, s);
    }
    return ksum(ls(t1), ls(t2), l, m, k - cnt, s + sum);
}