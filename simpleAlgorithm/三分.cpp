int l = 0, r = 1e6;
for (int times = 0; times < 100; times++) {
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    if (cal(lmid) < cal(rmid)) r = rmid;
    else l = lmid;
}

auto ans = 1e18L;
for (int i = l; i <= r; i++) ans = std::min(ans, cal(i));

void ternary_search() {
    int l, r;
    while (l < r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if (pred1()) {
            r = m1 - 1;
        } else if (pred2()) {
            l = m2;
        } else {
            l = m1;
            r = m2 - 1;
        }
    }
}