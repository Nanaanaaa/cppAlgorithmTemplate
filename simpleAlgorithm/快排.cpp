void quickSort(int* a, int l, int r) {
    if (l == r) {
        return;
    }
    auto [i, j, x] = std::tuple(l - 1, r + 1, a[(l + r) / 2]);
    while (i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) std::swap(a[i], a[j]);
    }
    quickSort(a, l, j);
    quickSort(a, j + 1, r);
}