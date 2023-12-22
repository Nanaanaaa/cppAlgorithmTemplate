struct Node {
    Node* ch[2]{};

    void add(int x) {
        Node* t = this;
        for (int i = 30; ~i; i--) {
            if (t->ch[x >> i & 1] == nullptr) {
                t->ch[x >> i & 1] = new Node;
            }
            t = t->ch[x >> i & 1];
        }
    }

    int query(int x) {
        Node* t = this;
        int res = 0;
        for (int i = 30; ~i; i--) {
            if (t->ch[~x >> i & 1] != nullptr) {
                res |= 1 << i;
                t = t->ch[~x >> i & 1];
            }
            else {
                t = t->ch[x >> i & 1];
            }
        }
        return res;
    }
};
