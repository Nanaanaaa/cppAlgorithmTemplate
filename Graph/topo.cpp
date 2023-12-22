std::vector<int> q;
for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
        q.push_back(i);
    }
}

for (int i = 0; i < q.size(); i++) {
    for (auto j : adj[q[i]]) {
        if (--deg[j] == 0) {
            q.push_back(j);
        }
    }
}