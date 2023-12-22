std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node* l;
    Node* r;
    int v, rank;
    int cnt;
    int siz;
    Node(int v) :l(nullptr), r(nullptr), v(v), cnt(1), siz(1), rank(rnd()) {}
};

void pull(Node* p) {
    p->siz = p->cnt + (p->l ? p->l->siz : 0) + (p->r ? p->r->siz : 0);
}

std::array<Node*, 2> split(Node* u, int v) {
    if (!u) return { nullptr, nullptr };
    if (u->v <= v) {
        auto [x, y] = split(u->r, v);
        u->r = x;
        pull(u);
        return { u, y };
    }
    else {
        auto [x, y] = split(u->l, v);
        u->l = y;
        pull(u);
        return { x, u };
    }
}

std::array<Node*, 3> select(Node* u, int k) {
    if (!u) return { nullptr, nullptr, nullptr };
    int lsiz = u->l ? u->l->siz : 0;
    if (k <= lsiz) {
        auto [l, m, r] = select(u->l, k);
        u->l = r;
        pull(u);
        return { l, m, u };
    }
    else if (k <= lsiz + u->cnt) {
        auto [l, r] = std::pair(u->l, u->r);
        u->l = u->r = nullptr;
        return { l, u, r };
    }
    else {
        auto [l, m, r] = select(u->r, k - lsiz - u->cnt);
        u->r = l;
        pull(u);
        return { u, m, r };
    }
}

Node* merge(Node* l, Node* r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }

    if (l->rank < r->rank) {
        l->r = merge(l->r, r);
        pull(l);
        return l;
    }
    else {
        r->l = merge(l, r->l);
        pull(r);
        return r;
    }
}

void add(Node*& root, int v) {
    auto [l, r] = split(root, v);
    auto [x, y] = split(l, v - 1);
    if (y == nullptr) {
        y = new Node(v);
    }
    else {
        y->cnt++;
        pull(y);
    }
    root = merge(merge(x, y), r);
}

void del(Node*& root, int v) {
    auto [l, r] = split(root, v);
    auto [x, y] = split(l, v - 1);
    if (y->cnt > 1) {
        y->cnt--;
        pull(y);
        x = merge(x, y);
    }
    else {
        if (l == y) {
            l = nullptr;
        }
        delete y;
    }
    root = merge(x, r);
}

int queryRank(Node*& root, Node* t, int v) {
    auto [l, r] = split(t, v - 1);
    int res = 1 + (l ? l->siz : 0);
    root = merge(l, r);
    return res;
}

int queryVal(Node*& root, Node* t, int k) {
    auto [l, m, r] = select(t, k);
    int res = m->v;
    root = merge(merge(l, m), r);
    return res;
}

int findPrev(Node*& root, int v) {
    auto [l, r] = split(root, v - 1);
    int res = queryVal(root, l, l->siz);
    root = merge(l, r);
    return res;
}

int findNext(Node*& root, int v) {
    auto [l, r] = split(root, v);
    int res = queryVal(root, r, 1);
    root = merge(l, r);
    return res;
}