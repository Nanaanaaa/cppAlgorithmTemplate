#include <bits/stdc++.h>

namespace stdv = std::views;
namespace stdr = std::ranges;

using i64 = long long;

constexpr int V = 1E9 + 1, N = 30 * 4E5;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int cnt = 0;
    i64 sum = 0;
};

Node* pool = (Node*)calloc(N, sizeof(Node));
int idx = 0;

void modify(Node*& p, int l, int r, int x, int v) {
    if (p == nullptr) {
        p = &pool[idx++];
    }
    p->sum += v * x;
    p->cnt += v;
    if (r - l == 1) {
        return;
    }
    int m = std::midpoint(l, r);
    if (x < m) {
        modify(p->l, l, m, x, v);
    } else {
        modify(p->r, m, r, x, v);
    }
}
void modify(Node*& p, int x, int v) {
    modify(p, 0, V, x, v);
}

int find(Node* p, int l, int r, i64 sum) {
    if (!p) {
        return 0;
    }
    if (p->sum > sum && r - l == 1) {
        return sum / l;
    }
    int m = std::midpoint(l, r);
    auto t = p->l;
    if (t && t->sum > sum) {
        return find(t, l, m, sum);
    }
    return (!t ? 0 : t->cnt) + find(p->r, m, r, sum - (!t ? 0 : t->sum));
}
int find(Node* p, i64 sum) {
    return find(p, 0, V, sum);
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    Node* root = new Node;
    i64 sumneg = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            modify(root, a[i], 1);
        } else {
            sumneg += -a[i];
        }
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--;

        if (a[x] > 0) {
            modify(root, a[x], -1);
        } else {
            sumneg -= -a[x];
        }
        a[x] = y;
        if (a[x] > 0) {
            modify(root, a[x], 1);
        } else {
            sumneg += -a[x];
        }

        std::cout << find(root, sumneg) + 1 << "\n";
    }

    return 0;
}