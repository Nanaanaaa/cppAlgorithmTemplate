#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace pbds = __gnu_pbds;
using P = std::pair<int, int>;
using tree = pbds::tree<P, pbds::null_type, std::less<P>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    tree set;

    for (int i = 0; i < n; i++) {
        int opt, x;
        std::cin >> opt >> x;

        if (opt == 1) { // 插入x
            set.insert({ x, i });
        } else if (opt == 2) { // 删除x
            auto it = set.lower_bound({ x, 0 });
            if (it != set.end() && it->first == x) {
                set.erase(it);
            }
        } else if (opt == 3) { // 查询x的排名(1base)
            std::cout << set.order_of_key({ x, 0 }) + 1 << "\n";
        } else if (opt == 4) { // 查询排名x的数字
            std::cout << set.find_by_order(x - 1)->first << "\n";
        } else if (opt == 5) { // 查询x的前驱
            auto it = set.lower_bound({ x, 0 });
            if (it == set.begin()) {
                std::cout << -1 << "\n";
            } else {
                std::cout << std::prev(it)->first << "\n";
            }
        } else if (opt == 6) { // 查询x的后继
            auto it = set.upper_bound({ x, n });
            if (it == set.end()) {
                std::cout << -1 << "\n";
            } else {
                std::cout << it->first << "\n";
            }
        }
    }

    return 0;
}