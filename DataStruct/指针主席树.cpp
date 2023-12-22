constexpr int V = 1e9 + 1;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int cnt = 0;
    Node(Node* t) {
        if (t != nullptr) {
            *this = *t;
        }
    }
};

constexpr int lcnt(const Node* t) {
    return t && t->l ? t->l->cnt : 0;
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
Node* add(Node* p, int x, int v) {
    return add(p, 0, V, x, v);
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
int kmin(Node* t1, Node* t2, int k) {
    return kmin(t1, t2, 0, V, k);
}

int kmax(Node* t1, Node* t2, int l, int r, int k) {
    if (r - l == 1) {
        return l;
    }
    int cnt = rcnt(t2) - rcnt(t1);
    int m = (l + r) / 2;
    if (cnt > k) {
        return kmax(rs(t1), rs(t2), m, r, k);
    }
    return kmax(ls(t1), ls(t2), l, m, k - cnt);
}
int kmax(Node* t1, Node* t2, int k) {
    return kmax(t1, t2, 0, V, k);
}