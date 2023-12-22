struct Node {
    Node* ch[2]{};
    int v = 0, cnt = 0;

    void pull() {
        cnt = v;
        if (ch[0] != nullptr) cnt += ch[0]->cnt;
        if (ch[1] != nullptr) cnt += ch[1]->cnt;
    }
};

void add(Node* t, int i, int x) {
    if (i == -1) {
        t->v++;
        t->pull();
        return;
    }
    if (t->ch[x >> i & 1] == nullptr) {
        t->ch[x >> i & 1] = new Node();
    }
    add(t->ch[x >> i & 1], i - 1, x);
    t->pull();
}