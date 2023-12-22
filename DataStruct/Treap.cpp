std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node* ch[2];
    int v, rank;
    int cnt;
    int siz;

    Node(int v) : ch{ nullptr, nullptr }, v(v), cnt(1), siz(1), rank(rnd()) {}

    void pull() {
        siz = cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
    }
} *root;

enum rootType { LF = 1, RT = 0 };

void rotate(Node*& cur, rootType dir) {
    Node* tmp = cur->ch[dir];
    cur->ch[dir] = tmp->ch[!dir];
    tmp->ch[!dir] = cur;
    tmp->pull(), cur->pull();
    cur = tmp;
}

void insert(Node*& cur, int v) {
    if (cur == nullptr) {
        cur = new Node(v);
        return;
    }
    else if (v == cur->v) {
        cur->cnt++;
        cur->siz++;
    }
    else if (v < cur->v) {
        insert(cur->ch[0], v);
        if (cur->ch[0]->rank < cur->rank) {

            rotate(cur, RT);
        }
        cur->pull();
    }
    else {
        insert(cur->ch[1], v);
        if (cur->ch[1]->rank < cur->rank) {
            rotate(cur, LF);
        }
        cur->pull();
    }
}

int queryv(Node* cur, int rank) {
    int lsiz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (rank <= lsiz) {
        return queryv(cur->ch[0], rank);
    }
    else if (rank <= lsiz + cur->cnt) {
        return cur->v;
    }
    else {
        return queryv(cur->ch[1], rank - lsiz - cur->cnt);
    }
}

int queryRank(Node* cur, int v) {
    int lsiz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (v == cur->v) {
        return lsiz + 1;
    }
    else if (v < cur->v) {
        if (cur->ch[0] != nullptr) {
            return queryRank(cur->ch[0], v);
        }
        else {
            return 1;
        }
    }
    else {
        if (cur->ch[1] != nullptr) {
            return lsiz + cur->cnt + queryRank(cur->ch[1], v);
        }
        else {
            return cur->siz + 1;
        }
    }
}

int queryPrev(Node* cur, int v) {
    if (v <= cur->v) {
        if (cur->ch[0] != nullptr) return queryPrev(cur->ch[0], v);
    }
    else {
        int ans = cur->v;
        if (cur->ch[1] != nullptr) queryPrev(cur->ch[1], v);
        return ans;
    }
    return -1;
}

int queryNext(Node* cur, int v) {
    if (v >= cur->v) {
        if (cur->ch[1] != nullptr) return queryNext(cur->ch[1], v);
    }
    else {
        int ans = cur->v;
        if (cur->ch[0] != nullptr) queryNext(cur->ch[0], v);
        return ans;
    }
    return -1;
}
