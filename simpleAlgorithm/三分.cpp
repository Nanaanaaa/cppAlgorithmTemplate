while (r - l > 2) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    if (check()) {
        l = m1;
    } else {
        r = m2;
    }
}

for (int i = l; i <= r; i++) {
    ...
}