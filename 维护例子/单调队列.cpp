auto getmin = [&](const std::vector<int>& a, int k) {
    std::deque<int> q;
    std::vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(a[q.front()]);
        }
    }
    return res;
};

auto getmax = [&](const std::vector<int>& a, int k) {
    std::deque<int> q;
    std::vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(a[q.front()]);
        }
    }
    return res;
};