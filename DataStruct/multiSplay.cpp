struct Node {
    Node* ch[2];
    Node* p;
    int v;
    int size;
    int cnt;

    Node(int v, Node* p = nullptr): ch{ nullptr, nullptr }, p(p), v(v), cnt(1), size(1) {}

    void pull() {
        size = cnt;
        if (ch[0] != nullptr) {
            size += ch[0]->size;
        }
        if (ch[1] != nullptr) {
            size += ch[1]->size;
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
}*root;

Node* insert(Node*& u, int v) {
    Node* p = nullptr;
    while (u) {
        if (u->v == v) {
            break;
        }
        p = u;
        u = u->ch[v > u->v];
    }
    if (u) {
        u->cnt++;
    }
    else {
        u = new Node(v, p);
        if (p) {
            p->ch[v > p->v] = u;
        }
    }
    u->splay();
    return u;
}

Node* select(Node* t, int k) {
    auto getsize = [](Node* u) {
        return u ? u->size : 0;
    };
    if (k < getsize(t->ch[0])) {
        return select(t->ch[0], k);
    }
    else if (k >= getsize(t->ch[0]) + t->cnt) {
        return select(t->ch[1], k - getsize(t->ch[0]) - t->cnt);
    }
    return t;
}