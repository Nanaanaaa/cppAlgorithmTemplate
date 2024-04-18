struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int cnt = 0;
    i64 sum = 0;
};

Node* add(Node* t, int l, int r, int p, int v) {
    Node* x = new Node;
    if (t) {
        *x = *t;
    }
    x->cnt += 1;
    x->sum += v;
    if (r - l == 1) {
        return x;
    }
    int m = (l + r) / 2;
    if (p < m) {
        x->l = add(x->l, l, m, p, v);
    }
    else {
        x->r = add(x->r, m, r, p, v);
    }
    return x;
}

int find(Node* tl, Node* tr, int l, int r, int x) {
    if (r <= x) {
        return -1;
    }
    if (l >= x) {
        int cnt = (tr ? tr->cnt : 0) - (tl ? tl->cnt : 0);
        if (cnt == 0) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
    }
    int m = (l + r) / 2;
    int res = find(tl ? tl->l : tl, tr ? tr->l : tr, l, m, x);
    if (res == -1) {
        res = find(tl ? tl->r : tl, tr ? tr->r : tr, m, r, x);
    }
    return res;
}

std::pair<int, i64> get(Node* t, int l, int r, int x, int y) {
    if (l >= y || r <= x || !t) {
        return { 0, 0LL };
    }
    if (l >= x && r <= y) {
        return { t->cnt, t->sum };
    }
    int m = (l + r) / 2;
    auto [cl, sl] = get(t->l, l, m, x, y);
    auto [cr, sr] = get(t->r, m, r, x, y);
    return { cl + cr, sl + sr };
}

struct Tree {
    int add = 0;
    int val = 0;
    int id = 0;
    Tree* ch[2] = {};
    Tree* p = nullptr;
};

int pos(Tree* t) {
    return t->p->ch[1] == t;
}

void add(Tree* t, int v) {
    t->val += v;
    t->add += v;
}

void push(Tree* t) {
    if (t->ch[0]) {
        add(t->ch[0], t->add);
    }
    if (t->ch[1]) {
        add(t->ch[1], t->add);
    }
    t->add = 0;
}

void rotate(Tree* t) {
    Tree* q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) t->ch[x]->p = q;
    t->p = q->p;
    if (q->p) q->p->ch[pos(q)] = t;
    t->ch[x] = q;
    q->p = t;
}

void splay(Tree* t) {
    std::vector<Tree*> s;
    for (Tree* i = t; i->p; i = i->p) s.push_back(i->p);
    while (!s.empty()) {
        push(s.back());
        s.pop_back();
    }
    push(t);
    while (t->p) {
        if (t->p->p) {
            if (pos(t) == pos(t->p)) rotate(t->p);
            else rotate(t);
        }
        rotate(t);
    }
}

void insert(Tree*& t, Tree* x, Tree* p = nullptr) {
    if (!t) {
        t = x;
        x->p = p;
        return;
    }

    push(t);
    if (x->val < t->val) {
        insert(t->ch[0], x, t);
    }
    else {
        insert(t->ch[1], x, t);
    }
}

void dfs(Tree* t) {
    if (!t) {
        return;
    }
    push(t);
    dfs(t->ch[0]);
    std::cerr << t->val << " ";
    dfs(t->ch[1]);
}

std::pair<Tree*, Tree*> split(Tree* t, int x) {
    if (!t) {
        return { t, t };
    }
    Tree* v = nullptr;
    Tree* j = t;
    for (Tree* i = t; i; ) {
        push(i);
        j = i;
        if (i->val >= x) {
            v = i;
            i = i->ch[0];
        }
        else {
            i = i->ch[1];
        }
    }

    splay(j);
    if (!v) {
        return { j, nullptr };
    }

    splay(v);

    Tree* u = v->ch[0];
    if (u) {
        v->ch[0] = u->p = nullptr;
    }
    // std::cerr << "split " << x << "\n";
    // dfs(u);
    // std::cerr << "\n";
    // dfs(v);
    // std::cerr << "\n";
    return { u, v };
}

Tree* merge(Tree* l, Tree* r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    Tree* i = l;
    while (i->ch[1]) {
        i = i->ch[1];
    }
    splay(i);
    i->ch[1] = r;
    r->p = i;
    return i;
}


struct Node {
    Node* ch[2], * p;
    bool rev;
    int siz = 1;
    Node() : ch{ nullptr, nullptr }, p(nullptr), rev(false) {}
};
void reverse(Node* t) {
    if (t) {
        std::swap(t->ch[0], t->ch[1]);
        t->rev ^= 1;
    }
}
void push(Node* t) {
    if (t->rev) {
        reverse(t->ch[0]);
        reverse(t->ch[1]);
        t->rev = false;
    }
}
void pull(Node* t) {
    t->siz = (t->ch[0] ? t->ch[0]->siz : 0) + 1 + (t->ch[1] ? t->ch[1]->siz : 0);
}
bool isroot(Node* t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node* t) {
    return t->p->ch[1] == t;
}
void pushAll(Node* t) {
    if (!isroot(t)) {
        pushAll(t->p);
    }
    push(t);
}
void rotate(Node* t) {
    Node* q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    pull(q);
}
void splay(Node* t) {
    pushAll(t);
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            }
            else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}
void access(Node* t) {
    for (Node* i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        i->ch[1] = q;
        pull(i);
    }
    splay(t);
}
void makeroot(Node* t) {
    access(t);
    reverse(t);
}
void link(Node* x, Node* y) {
    makeroot(x);
    x->p = y;
}
void split(Node* x, Node* y) {
    makeroot(x);
    access(y);
}
void cut(Node* x, Node* y) {
    split(x, y);
    x->p = y->ch[0] = nullptr;
    pull(y);
}
int dist(Node* x, Node* y) {
    split(x, y);
    return y->siz - 1;
}


struct Matrix : std::array<std::array<i64, 4>, 4> {
    Matrix(i64 v = 0) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                (*this)[i][j] = (i == j ? v : inf);
            }
        }
    }
};

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c(inf);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                c[i][k] = std::min(c[i][k], a[i][j] + b[j][k]);
            }
        }
        c[i][3] = std::min(c[i][3], a[i][3]);
    }
    c[3][3] = 0;
    return c;
}

struct Node {
    Node* ch[2], * p;
    i64 sumg = 0;
    i64 sumh = 0;
    i64 sumb = 0;
    i64 g = 0;
    i64 h = 0;
    i64 b = 0;
    Matrix mat;
    Matrix prd;
    std::array<i64, 4> ans{};
    Node() : ch{ nullptr, nullptr }, p(nullptr) {}

    void update() {
        mat = Matrix(inf);
        mat[0][0] = b + h - g + sumg;
        mat[1][1] = mat[1][2] = mat[1][3] = h + sumh;
        mat[2][0] = mat[2][1] = mat[2][2] = mat[2][3] = b + h + sumb;
        mat[3][3] = 0;
    }
};
void push(Node* t) {

}
void pull(Node* t) {
    t->prd = (t->ch[0] ? t->ch[0]->prd : Matrix()) * t->mat * (t->ch[1] ? t->ch[1]->prd : Matrix());
}
bool isroot(Node* t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node* t) {
    return t->p->ch[1] == t;
}
void pushAll(Node* t) {
    if (!isroot(t)) {
        pushAll(t->p);
    }
    push(t);
}
void rotate(Node* t) {
    Node* q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    pull(q);
}
void splay(Node* t) {
    pushAll(t);
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            }
            else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}

std::array<i64, 4> get(Node* t) {
    std::array<i64, 4> ans;
    ans.fill(inf);
    ans[3] = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            ans[i] = std::min(ans[i], t->prd[i][j]);
        }
    }
    return ans;
}

void access(Node* t) {
    std::array<i64, 4> old{};
    for (Node* i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        if (i->ch[1]) {
            auto res = get(i->ch[1]);
            i->sumg += res[0];
            i->sumh += std::min({ res[1], res[2], res[3] });
            i->sumb += std::min({ res[0], res[1], res[2], res[3] });
        }
        i->ch[1] = q;
        i->sumg -= old[0];
        i->sumh -= std::min({ old[1], old[2], old[3] });
        i->sumb -= std::min({ old[0], old[1], old[2], old[3] });
        old = get(i);
        i->update();
        pull(i);
    }
    splay(t);
}
