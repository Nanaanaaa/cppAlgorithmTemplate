std::vector<std::array<int, 2>> mergeInterval(std::vector<std::array<int, 2>>& seg) {
    std::vector<std::array<int, 2>> res;
    std::sort(seg.begin(), seg.end());
    for (auto [l, r] : seg) {
        if (!res.empty() && l <= res.back()[1]) {
            res.back()[1] = std::max(res.back()[1], r);
        }
        else {
            res.push_back({ l, r });
        }
    }
    return res;
}
