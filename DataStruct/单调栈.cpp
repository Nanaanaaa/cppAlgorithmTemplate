std::vector<int> stk;
std::vector<int> l(n), r(n);
for (int i = 0; i < n; i++) {
    while (!stk.empty() && a[stk.back()] <= a[i]) {
        stk.pop_back();
    }
    l[i] = stk.empty() ? -1 : stk.back();
    stk.push_back(i);
}
stk.clear();
for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && a[stk.back()] <= a[i]) {
        stk.pop_back();
    }
    r[i] = stk.empty() ? n : stk.back();
    stk.push_back(i);
}