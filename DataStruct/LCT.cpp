struct LCT {
    LCT* ch[2];
    LCT* p;
    int v, size;
    int sum;
    int rev;

    LCT(int v, LCT* p = nullptr): ch{ nullptr, nullptr }, v(v), size(1), rev(0), sum(v), p(p) {}

    void pull() {
        sum = v;
        if (ch[0] != nullptr) {
            sum ^= ch[0]->sum;
        }
        if (ch[1] != nullptr) {
            sum ^= ch[1]->sum;
        }
    }

    void pushrev() {
        std::swap(ch[0], ch[1]);
        rev ^= 1;
    }

    void push() {
        if (rev) {
            for (int i : {0, 1}) {
                if (ch[i] != nullptr) {
                    ch[i]->pushrev();
                }
            }
            rev = 0;
        }
    }

    bool pos() {
        return p->ch[1] == this;
    }

    bool isRoot() {
        return p == nullptr || p->ch[0] != this && p->ch[1] != this;
    }

    void rotate() {
        LCT* q = p;
        bool x = !pos();
        q->ch[!x] = ch[x];
        if (ch[x]) {
            ch[x]->p = q;
        }
        p = q->p;
        if (!q->isRoot() && q->p) {
            q->p->ch[q->pos()] = this;
        }
        ch[x] = q;
        q->p = this;
        q->pull();
        pull();
    }

    void splay() {
        std::vector<LCT*> stk;
        auto q = this;
        stk.push_back(q);
        while (!q->isRoot()) {
            stk.push_back(q = q->p);
        }
        while (!stk.empty()) {
            stk.back()->push();
            stk.pop_back();
        }

        while (!isRoot()) {
            if (!p->isRoot()) {
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

    void access() { // 建立一条根节点到当前点的路径, 同时把x变成splay的根节点
        for (LCT* x = this, *y = nullptr; x != nullptr; y = x, x = x->p) {
            x->splay();
            x->ch[1] = y;
            x->pull();
        }
        splay();
    }

    void makeRoot() { // 当前点变为原树的根节点
        access();
        pushrev();
    }

    LCT* findRoot() { // 找到当前原树的根节点，再将原树的根节点旋转到splay的根节点的位置
        access();
        auto x = this;
        for (;x->ch[0]; x = x->ch[0]) {
            x->push();
        }
        x->splay();
        return x;
    }

    void split(LCT* g) { // 当前点到y建立一颗根为y的splay
        makeRoot();
        g->access();
    }
};

void link(LCT* x, LCT* y) {
    x->makeRoot();
    if (y->findRoot() != x) {
        x->p = y;
    }
}

void cut(LCT* x, LCT* y) {
    x->makeRoot();
    if (y->findRoot() == x && y->p == x && y->ch[0] == nullptr) {
        x->ch[1] = y->p = nullptr;
        x->pull();
    }
}

using Node = LCT;