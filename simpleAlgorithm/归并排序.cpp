i64 mergeSort(const std::vector<int>& a, int l, int r) {
    if (r - l == 1) {
        return 0;
    }
    int m = (l + r) / 2;
    i64 cnt = mergeSort(a, l, m) + mergeSort(a, m, r);

    int i = l, j = m;
    std::vector<int> t;
    while (i < m && j < r) {
        if (a[i] <= a[j]) {
            t.push_back(a[i++]);
        } else {
            cnt += m - i;
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
    return cnt;
}

template<typename RandomIt>
void mergeSort(RandomIt l, RandomIt r) {
    if (std::distance(l, r) == 1) {
        return;
    }

    auto m = l + std::distance(l, r) / 2;

    mergeSort(l, m);
    mergeSort(m, r);

    std::inplace_merge(l, m, r);
}