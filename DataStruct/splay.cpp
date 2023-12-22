struct Node {
    Node* ch[2];
    Node* p;
    int v;
    int siz;

    Node(int v, Node* p = nullptr) : ch{ nullptr, nullptr }, p(p), v(v), siz(1) {}

    void pull() {
        siz = 1;
        if (ch[0] != nullptr) {
            siz += ch[0]->siz;
        }
        if (ch[1] != nullptr) {
            siz += ch[1]->siz;
        }
    }

    void rotate() {
        Node* q = p;
        bool x = !pos();
        q->ch[!x] = ch[x];
        if (ch[x] != nullptr) {
            ch[x]->p = q;
        }
        p = q->p;
        if (q->p != nullptr) {
            q->p->ch[q->pos()] = this;
        }
        ch[x] = q;
        q->p = this;
        q->pull();
        pull();
    }

    bool pos() {
        return p->ch[1] == this;
    }

    void splay(Node* g = nullptr) {
        while (p != g) {
            if (p->p != g) {
                if (pos() == p->pos()) {
                    p->rotate();
                }
                else {
                    rotate();
                }
            }
            rotate();
        }
        pull();
    }
};

Node* insert(Node*& u, int v) {
    Node* p = nullptr;
    while (u) {
        p = u;
        u = u->ch[v > u->v];
    }
    u = new Node(v, p);
    if (p) {
        p->ch[v > p->v] = u;
    }
    u->splay();
    return u;
}

Node* select(Node* t, int k) {
    if (t->ch[0] != nullptr) {
        if (k < t->ch[0]->siz) {
            return select(t->ch[0], k);
        }
        else {
            k -= t->ch[0]->siz;
        }
    }
    if (k == 0) {
        return t;
    }
    k--;
    return select(t->ch[1], k);
}