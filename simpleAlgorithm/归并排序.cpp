void mergeSort(int* a, int l, int r) {
    if (r - l == 1) {
        return;
    }
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m, r);

    int i = l, j = m;
    std::vector<int> t;
    while (i < m && j < r) {
        if (a[i] < a[j]) {
            t.push_back(a[i++]);
        }
        else {
            t.push_back(a[j++]);
        }
    }
    for (; i < m; i++) {
        t.push_back(a[i]);
    }
    for (; j < r; j++) {
        t.push_back(a[j]);
    }
    for (int i = l, j = 0; i < r; i++, j++) {
        a[i] = t[j];
    }
}